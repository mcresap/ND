#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

typedef struct copy_stat{
	int bytes;
	int files;
	int dir;
}
copy_stat;

int reccopy(char *, struct stat *, char *, copy_stat *); //recurse through directories
int filecopy(char *, char *, copy_stat *);

int main(int argc, char *argv[]){
	copy_stat c;
	c.bytes = 0;
	c.dir = 0;
	c.files = 0;
	struct stat filetype;
	if (stat(argv[1], &filetype) < 0){
		fprintf(stderr, "unable to open %s: %s\n", argv[1], strerror(errno));
		return -1;
	}
	if ((S_ISDIR(filetype.st_mode)) != 0){ //check if file element was a directory
		reccopy(argv[1], &filetype, argv[2], &c);
		c.dir += 1;
	}
	else if ((S_ISREG(filetype.st_mode)) != 0){ //if file is a file
		filecopy(argv[1], argv[2], &c);
		c.files +=1;
	}
	else{ 
	}
	printf("copied %d directories, %d files, and %d bytes from %s to %s\n", c.dir, c.files, c.bytes, argv[1], argv[2]);
	return 0;
}

int reccopy(char *x, struct stat *filetype, char *newpath, copy_stat* c){
	mkdir(newpath, filetype->st_mode);
	struct stat newfile;
	DIR *rdir = opendir(x);
	if (rdir == NULL){
		fprintf(stderr, "couldn't open directory %s: %s\n", x, strerror(errno));
		return -1;
	}
	
	struct dirent *reddir;
	while((reddir = readdir(rdir)) != NULL){
		char dest [strlen(x) + 1 + strlen(reddir->d_name) + 1]; //space for destination
		strcpy(dest, x); //directory copied from
		strcat(dest, "/"); //one step of path
		strcat(dest, reddir->d_name); //name in directory
		int er = stat(dest, &newfile);
		if (er < 0){
			fprintf(stderr, "error when calling stat: %s\n", strerror(errno));
		}
		char newerpath[strlen(newpath) + 1 + strlen(reddir->d_name) + 1]; //where you're copying directory to
		strcpy(newerpath, newpath);
		strcat(newerpath, "/");
		strcat(newerpath, reddir->d_name);
		if ((strcmp(reddir->d_name, ".")) != 0 && (strcmp(reddir->d_name, "..")) != 0){
			printf("Src: %s\nDest: %s\n", dest, newerpath);
			if ((S_ISDIR(newfile.st_mode)) != 0){
				reccopy(dest, &newfile, newerpath, c);
				c->dir += 1;
			}
			else if ((S_ISREG(newfile.st_mode)) != 0){
				filecopy(dest, newerpath, c);
				c->files += 1;
			}
			else{ 
			}
		}
	}
	return 0;
}

int filecopy(char *x, char *y, copy_stat* c){
	int rfile = open(x, O_RDONLY); //open first file to read in order to copy
	if (rfile < 0){
		fprintf(stderr, "couldn't open %s: %s\n", x, strerror(errno));
		return -1;
	}
	int wfile = open(y, O_CREAT | O_WRONLY, 0666); //start writing to new destination
	if (wfile<0){
		fprintf(stderr, "unable to open %s: %s\n", y, strerror(errno));
	}

	char buffer [4096]; //create buffer size 4096
	int rread, wwrite, nwritten;
	while((rread = read(rfile, buffer, 4096)) != 0){
		if (rread == -1){
			fprintf(stderr, "couldn't read %s: %s\n", x, strerror(errno));
			return -1;
		}
		nwritten = 0;
		while (nwritten != rread){
			wwrite = write(wfile, buffer + nwritten, rread - nwritten);
			if (wwrite <0){
				fprintf(stderr, "couldn't open %s: %s\n", x, strerror(errno));
				return -1;
			}
			nwritten += wwrite;
			c->bytes += wwrite; //count # bytes copied
		}
	}
	if (rfile >= 0) close(rfile);
	if (wfile >=0) close(wfile);
	return 0;	
}
