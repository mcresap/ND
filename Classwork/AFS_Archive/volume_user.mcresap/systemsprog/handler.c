/* handler.c: HTTP Request Handlers */

#include "spidey.h"

#include <errno.h>
#include <limits.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

/* Internal Declarations */
HTTPStatus handle_browse_request(Request *request);
HTTPStatus handle_file_request(Request *request);
HTTPStatus handle_cgi_request(Request *request);
HTTPStatus handle_error(Request *request, HTTPStatus status);

/**
 * Handle HTTP Request.
 *
 * @param   r           HTTP Request structure
 * @return  Status of the HTTP request.
 *
 * This parses a request, determines the request path, determines the request
 * type, and then dispatches to the appropriate handler type.
 *
 * On error, handle_error should be used with an appropriate HTTP status code.
 **/

HTTPStatus  handle_request(Request *r) { //a dispatch function that uses parse_request, determine_request_path, and stat and accessto determine which handler to call
  HTTPStatus result;

  /* Parse request */
  if (parse_request(r) == -1) {
      fprintf(stderr, "Could not parse request: %s\n", strerror(errno));
      result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
      return result;
  }
  //done parsing request

  /* Determine request path */
  // Real path corrsponding to URI and RootPath
  // Set path
  r->path = determine_request_path(r->uri); // HTTP uniform resource identifier

  // Check path
  if (r->path == NULL) {
    result = handle_error(r, HTTP_STATUS_NOT_FOUND);
    return result;
  }

  debug("HTTP REQUEST PATH: %s", r->path);

  /* Dispatch to appropriate request handler type based on file type */
  struct stat s;

  if(stat(r->path, &s) < 0){
    fprintf(stderr, "Could not STAT: %s\n", strerror(errno));
    result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
    return result;
  }

  if (S_ISDIR(s.st_mode)) {
    result = handle_browse_request(r);
  }
  else if (!access(r->path, X_OK)) {
    result = handle_cgi_request(r);
  }
   else if (S_ISREG(s.st_mode)) {
    result = handle_file_request(r);
  }
  else {
    result = handle_error(r, HTTP_STATUS_BAD_REQUEST);
    //free_request(r);
  }

  log("HTTP REQUEST STATUS: %s", http_status_string(result));
  return result;
}

/**
 * Handle browse request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP browse request.
 *
 * This lists the contents of a directory in HTML.
 *
 * If the path cannot be opened or scanned as a directory, then handle error
 * with HTTP_STATUS_NOT_FOUND.
 **/
HTTPStatus  handle_browse_request(Request *r) {
  struct dirent **entries;
  int n =0;

  /* Open a directory for reading or scanning */
  if ((n = scandir(r->path, &entries, NULL, alphasort)) == -1)
    return handle_error(r, HTTP_STATUS_NOT_FOUND);

  /* Write HTTP Header with OK Status and text/html Content-Type */
  fputs("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n", r->file);

  /* For each entry in directory, emit HTML list item */
  fputs("<html>\r\n", r->file);
  fputs("<ul>", r->file); //add ul to entries

  for (int i=0; i < n; i++){
    if (entries[i]->d_name && !streq(entries[i]->d_name, ".")){
      fprintf(r->file, "<li><a href=\"%s/%s\">%s</a></li>", streq(r->uri, "/") ? "" : r->uri, entries[i]->d_name, entries[i]->d_name);
    }
    free(entries[i]);
  }
  free(entries);
  fputs("</ul></html>\r\n", r->file);

  /* Flush socket, return OK */
  fflush(r->file);

  return HTTP_STATUS_OK;
}

/**
 * Handle file request.
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This opens and streams the contents of the specified file to the socket.
 *
 * If the path cannot be opened for reading, then handle error with
 * HTTP_STATUS_NOT_FOUND.
 **/
HTTPStatus  handle_file_request(Request *r) {
    FILE *fs;
    char buffer[BUFSIZ];
    char *mimetype = NULL;
    size_t nread;

    /* Open file for reading */
    if (!(fs = fopen(r->path, "r"))){
        debug("Could not open file");
        return handle_error(r, HTTP_STATUS_NOT_FOUND);
    }
    /* Determine mimetype */
    mimetype = determine_mimetype(r->path);
    /* Write HTTP Headers with OK status and determined Content-Type */
    fprintf(r->file, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", mimetype);
    /* Read from file and write to socket in chunks */
    while ((nread = fread(buffer, 1, BUFSIZ, fs)) > 0)
        fwrite(buffer, 1, nread, r->file);
    /* Close file, flush socket, deallocate mimetype, return OK */
    fclose(fs);
    fflush(r->file);
    free(mimetype);
    return HTTP_STATUS_OK;

//fail:
    /* Close file, free mimetype, return INTERNAL_SERVER_ERROR */
//    return HTTP_STATUS_INTERNAL_SERVER_ERROR;
}

/**
 * Handle CGI request
 *
 * @param   r           HTTP Request structure.
 * @return  Status of the HTTP file request.
 *
 * This popens and streams the results of the specified executables to the
 * socket.
 *
 * If the path cannot be popened, then handle error with
 * HTTP_STATUS_INTERNAL_SERVER_ERROR.
 **/
HTTPStatus handle_cgi_request(Request *r) {
  FILE *pfs;
  char buffer[BUFSIZ];

  struct header *header;

  /* Export CGI environment variables from request structure:
   * http://en.wikipedia.org/wiki/Common_Gateway_Interface */

  if (r->query){
    setenv("QUERY_STRING", r->query, 1);
	}

  setenv("REQUEST_METHOD", r->method, 1);
  setenv("REQUEST_URI", r->uri, 1);
  setenv("DOCUMENT_ROOT", RootPath, 1);
  setenv("REMOTE_ADDR", r->host, 1);
  setenv("SERVER_PORT", Port, 1);
  setenv("REMOTE_PORT", r->port, 1);
  setenv("SCRIPT_FILENAME", r->path, 1);

  /* Export CGI environment variables from request headers */
  header = r->headers;
  while (header){
    if (header-> name && streq(header->name, "Accept-Language"))
      setenv("HTTP_ACCEPT_LANGUAGE", header->value, 1);
    else if (header-> name && streq(header->name, "Host"))
      setenv("HTTP_HOST", header->value, 1);
    else if (header-> name && streq(header->name, "Accept-Encoding"))
      setenv("HTTP_ACCEPT_ENCODING", header->value, 1);
    else if (header-> name && streq(header->name, "User-Agent"))
      setenv("HTTP_USER_AGENT", header->value, 1);
    else if (header-> name && streq(header->name, "Connection"))
      setenv("HTTP_CONNECTION", header->value, 1);
    else if (header-> name && streq(header->name, "Accept"))
      setenv("HTTP_ACCEPT", header->value, 1);
    header = header->next;
	}
  /* POpen CGI Script */
  pfs = popen(r->path, "r");
  if (!pfs){
      return handle_error(r, HTTP_STATUS_INTERNAL_SERVER_ERROR);
  }
  /* Copy data from popen to socket */
  while (fgets(buffer, BUFSIZ, pfs) != NULL){
      fputs(buffer, r->file);
  }
  /* Close popen, flush socket, return OK */
  pclose(pfs);
  fflush(r->file);
  return HTTP_STATUS_OK;
}

/**
* Handle displaying error page
*
* @param   r           HTTP Request structure.
* @return  Status of the HTTP error request.
*
* This writes an HTTP status error code and then generates an HTML message to
* notify the user of the error.
**/
HTTPStatus  handle_error(Request *r, HTTPStatus status) {
  const char *status_string = http_status_string(status);

  /* Write HTTP Header */
  fprintf(r->file, "HTTP1.0 %s\r\nContent-Type: text/html\r\n\r\n", status_string);
  /* Write HTML Description of Error*/
  fprintf(r->file, "<html>\n<h1>%s</h1>\n", status_string);
  fprintf(r->file, "<h2>Error</h2>\r\n</html>\r\n");

  /* Return specified status */
  fflush(r->file);
  return status;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
