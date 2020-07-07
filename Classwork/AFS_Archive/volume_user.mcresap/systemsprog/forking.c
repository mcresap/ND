/* forking.c: Forking HTTP Server */

#include "spidey.h"

#include <errno.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>


/**
 * Fork incoming HTTP requests to handle the concurrently.
 *
 * @param   sfd         Server socket file descriptor.
 * @return  Exit status of server (EXIT_SUCCESS).
 *
 * The parent should accept a request and then fork off and let the child
 * handle the request.
 **/
int forking_server(int sfd) {
    Request *requests;
    /* Accept and handle HTTP request */
    while (true) {
    	 /* Accept request */
        requests = accept_request(sfd);
        if (!requests){
          continue;
        }
	/* Ignore children */
        signal(SIGCHLD, SIG_IGN);
	/* Fork off child process to handle request */
        pid_t pid;
        pid = fork();
        if (pid < 0){ // error - print error
            close(sfd);
            free_request(requests);
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
        }
        else if (pid == 0){ // child
            close(sfd); //close server socket
            handle_request(requests);
            exit(EXIT_SUCCESS);
        }
        else { // parent
            free_request(requests);
        }
    }

    /* Close server socket */
    close(sfd);
    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
