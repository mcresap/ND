/* single.c: Single User HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <string.h>

#include <unistd.h>

/**
 * Handle one HTTP request at a time.
 *
 * @param   sfd         Server socket file descriptor.
 * @return  Exit status of server (EXIT_SUCCESS).
 **/
int single_server(int sfd) { // use accept_request, handle_request and free_request

	Request *r;

	/* Accept and handle HTTP request */
	while (true) {

		/* Accept request */
	  // Call accept_request function
	  r = accept_request(sfd);
	  if (r == NULL) {
	    fprintf(stderr, "Failed to accept request: %s \n", strerror(errno));
            free_request(r);
            return EXIT_FAILURE;
	  }
        debug("got past accept");
	  /* Handle request */
	  // Call handle_request function
	  handle_request(r);
        debug("got past handle_req");
	  /* Free request */
	  // Call free_request function
	  free_request(r);
	}

	  /* Close server socket */
	  close(sfd);
	  return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
