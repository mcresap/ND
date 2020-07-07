/* utils.c: spidey utilities */

#include "spidey.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/**
 * Determine mime-type from file extension.
 *
 * @param   path        Path to file.
 * @return  An allocated string containing the mime-type of the specified file.
 *
 * This function first finds the file's extension and then scans the contents
 * of the MimeTypesPath file to determine which mimetype the file has.
 *
 * The MimeTypesPath file (typically /etc/mime.types) consists of rules in the
 * following format:
 *
 *  <MIMETYPE>      <EXT1> <EXT2> ...
 *
 * This function simply checks the file extension version each extension for
 * each mimetype and returns the mimetype on the first match.
 *
 * If no extension exists or no matching mimetype is found, then return
 * DefaultMimeType.
 *
 * This function returns an allocated string that must be free'd.
 **/
char * determine_mimetype(const char *path) {
    char *ext;
    char *mimetype;
    char *token;
    char buffer[BUFSIZ];
    FILE *fs = NULL;

    /* Find file extension */
    ext = strrchr(path, '.');
    if (ext == NULL)
        return strdup(DefaultMimeType);
    ext++;
    /*while (*ext != '\0'){ // go to end of string
        ext++;
    }
    while (*ext != '.'){ // go to last .
        ext--;
    }
    if (*ext != '.'){
        printf("Error finding file extension\n");
        goto fail;
    }
    ext++;*/
    /* Open MimeTypesPath file */
    fs = fopen(MimeTypesPath, "r");
    if (fs == NULL){
        log("Unable to fopen: %s\n", strerror(errno));
        return NULL;
    }
   /* if (!(fs= fopen(MimeTypesPath, "r"))){
        fprintf(stderr, "Error reading path\n");
        goto fail;
    }*/
    /* Scan file for matching file extensions */
    while (fgets(buffer, BUFSIZ, fs)){
            mimetype = strtok(buffer, WHITESPACE);
            if (mimetype == NULL)
                continue;
            while ((token = strtok(NULL, WHITESPACE)) != NULL){
                if (streq(ext, token)){
                    fclose(fs);
                    return strdup(mimetype);
                }
            }
    }
    return NULL;           
   /* while (fgets(buffer, BUFSIZ, fs) != NULL && sizeof(buffer) > 2){
        chomp(buffer); //remove trailing \n

        if (buffer[0] == '#' || streq(buffer, "\n")) {
          continue; // continue if line is empty or a comment
        }

        mimetype = strtok(buffer, "\t");
        if (mimetype== NULL) {
          continue; // continueif there is no tab in the line
        }

        token = strtok(NULL, "\t");
        if (token == NULL) {
          continue;
        }

        token = strtok(NULL, WHITESPACE);
        while (token) {
          token = skip_whitespace(token);
          if (streq(ext, token)){
            goto done;
          }
          else
            token = strtok(NULL, " ");
        }
    }
    goto fail;

fail:
    mimetype = DefaultMimeType;
done:
    if (fs){
        fclose(fs);
    }
    return strdup(mimetype);*/
}

/**
 * Determine actual filesystem path based on RootPath and URI.
 *
 * @param   uri         Resource path of URI.
 * @return  An allocated string containing the full path of the resource on the
 * local filesystem.
 *
 * This function uses realpath(3) to generate the realpath of the
 * file requested in the URI.
 *
 * As a security check, if the real path does not begin with the RootPath, then
 * return NULL.
 *
 * Otherwise, return a newly allocated string containing the real path.  This
 * string must later be free'd.
 **/
char * determine_request_path(const char *uri) {
     char buffer[BUFSIZ];
     char buffer2[BUFSIZ];
     if (uri[0]=='/')
        sprintf(buffer, "%s%s", RootPath, uri);
     else
         sprintf(buffer, "%s/%s", RootPath, uri);
    char *real_path = realpath(buffer, buffer2);
    if (!real_path){
        log("failed to get real path: %s", strerror(errno));
        return NULL;
    }
    if (strncmp(real_path, RootPath, strlen(RootPath) != 0))
        return NULL;
    return strdup(real_path);

     /*sprintf(path, "%s%s", RootPath, uri);
     realpath(path, real);
     if (strstr(real, RootPath) == NULL){
         return NULL; // return null if rootpath is not in real
     }
    
    return strdup(real);*/ // return a duplicate of real
   /* char path[BUFSIZ];
    char real[BUFSIZ];

    strcpy(path, RootPath);
    debug("uri: %s", uri);
    strcat(path, uri);
    debug("ROOT PATH: %s", RootPath);
    if(realpath(path, real) == NULL)
        fprintf(stderr, "Couldn't determine real path: %s\n", strerror(errno));

    log("Real path is %s", real);
    return strdup(real);*/

}

/**
 * Return static string corresponding to HTTP Status code.
 *
 * @param   status      HTTP Status.
 * @return  Corresponding HTTP Status string (or NULL if not present).
 *
 * http://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 **/
const char * http_status_string(HTTPStatus status) {
    static char *StatusStrings[] = {
        "200 OK",
        "400 Bad Request",
        "404 Not Found",
        "500 Internal Server Error",
        "418 I'm A Teapot",
    };
    if (status < 5 && status >=0)
        return StatusStrings[status];
    else
        return NULL;
    /*const char *status_string;
    if (status == HTTP_STATUS_OK)
        status_string = StatusStrings[0];
    else if (status == HTTP_STATUS_BAD_REQUEST)
        status_string = StatusStrings[1];
    else if (status == HTTP_STATUS_NOT_FOUND)
        status_string = StatusStrings[2];
    else if (status == HTTP_STATUS_INTERNAL_SERVER_ERROR)
        status_string = StatusStrings[3];
    else if (status == HTTP_STATUS_I_AM_A_TEAPOT)
        status_string = StatusStrings[4];
    return status_string;*/
}

/**
 * Advance string pointer pass all nonwhitespace characters
 *
 * @param   s           String.
 * @return  Point to first whitespace character in s.
 **/
char * skip_nonwhitespace(char *s) {
    /*while (!isspace(*s)){
        s++;
    }*/
    s=strpbrk(s, WHITESPACE);
    return s;
}

/**
 * Advance string pointer pass all whitespace characters
 *
 * @param   s           String.
 * @return  Point to first non-whitespace character in s.
 **/
char * skip_whitespace(char *s) {
    /*while (isspace(*s)){
        s++;
    }*/
    s=s+strspn(s, WHITESPACE);
    return s;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
