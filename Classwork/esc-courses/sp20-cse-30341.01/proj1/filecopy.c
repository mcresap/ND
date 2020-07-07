#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define BUFFSIZ 4096

int main (int argc, char *argv[]){
	int status = EXIT_FAILURE;

	if (argc > 3){
		printf("Too many arguments!\nusage: ./treecopy <sourcefile> <targetfile>");
	}
	if (argc < 3){
		printf("Not enough arguments!\nusage: ./treecopy <sourcefile> <targetfile>");
	}

	int rfile = open(argv[1], O_RDONLY); //open first file to read
	if (rfile<0){
		fprintf(stderr, "unable to open %s: %s\n", argv[1], strerror(errno));
		//goto clean;
		exit(1);
	}
	int wfile = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (wfile<0){
		fprintf(stderr, "unable to open %s: %s\n", argv[2], strerror(errno));
	}

	char buffer [BUFFSIZ]; //create buffer size 4096
	int rread;
	int wwrite;
	int bytes = 0;
	while((rread = read(rfile, buffer, BUFFSIZ)) > 0){
		int nwritten = 0;
		while (nwritten != rread){
			wwrite = write(wfile, buffer + nwritten, rread - nwritten);
			if (wwrite <0){
				fprintf(stderr, "unable to open %s: %s\n", argv[1], strerror(errno));
				//goto clean;
				exit(2);
			}
			nwritten += wwrite;
			bytes += wwrite; //count # bytes copied
		}
	}
	close(rfile);
	close(wfile);
	printf("copied %d bytes from %s to %s\n", bytes, argv[1], argv[2]);
	//return 0;
	exit(status);
}
