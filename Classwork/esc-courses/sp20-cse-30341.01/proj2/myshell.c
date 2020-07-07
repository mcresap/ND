//Maria Cresap
//mcresap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>

// initialize functions
void signalHandler(int signum);
int start_p(char *w[], char **nw, int i);
void wait_p(int p);

int main(int argc, char* argv[]){
	bool run = 1;

	while(run){
		printf("myshell> ");
		fflush(stdout);
		char line[1000]; //max number of letters
		fgets(line,1000,stdin); 

		char *words[100]; // max number of commands
		int nwords = 0; // counter
		words[nwords] = strtok(line," \t\n");
		if(words[nwords] == NULL){
			continue;
		}
		nwords++;
		while((words[nwords] = strtok(0," \t\n")) && nwords<=100){
			nwords++;
		}
		words[nwords] = 0;
		char ** newwords = words + 1;

		// start
		if(!strcmp(words[0],"start")){
			if(!words[1]){
				printf("myshell: Not enough arguments\n");
				continue;
			}
			pid_t pid = start_p(words,newwords, 1);
			if(pid!=-1){printf("myshell: process %d started\n", pid);}
		}

		// wait command
		else if(!strcmp(words[0],"wait")){
			wait_p(-1); // waitpid with -1 is same as wait
		}

		// waitfor command
		else if(!strcmp(words[0], "waitfor")){
			if(!words[1]){
				printf("myshell: Not enough arguments\n");
				continue;
			}
			int pid = atoi(words[1]);
			wait_p(pid);
		}

		// run command
			else if(!strcmp(words[0], "run")){
			if(!words[1]){
				printf("myshell: Not enough arguments\n");
				continue;
			}
			pid_t pid = start_p(words, newwords, 1);
			wait_p(pid);
		}

		// watch dog
			else if(!strcmp(words[0], "watchdog")){
			if(!words[1]){
				printf("myshell: Not enough arguments\n");
				continue;
			}

			if (signal(SIGCHLD, signalHandler) == SIG_ERR){
				printf("myshell: Signal failed: %s\n", strerror(errno));
			}

			int ts = atoi(words[1]);
			newwords++;
			pid_t pid = start_p(words,newwords,2);
			int tleft = sleep(ts);

			if(tleft == 0){
				printf("myshell: %d exceeded the time limit, killing it... \n", pid);
				if (kill(pid, SIGKILL) < 0){
					printf("myshell: Kill failed for process %d: %s\n", pid, strerror(errno));
				}
			}
			
			wait_p(pid);
		}

		// working dir
		else if(!strcmp(words[0], "pwd")){
			char cwd[1024];
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);
		}
		
		// changing directories
		else if(!strcmp(words[0], "chdir")){
			if(!words[1]){
				printf("myshell: Not enough arguments\n");
				continue;
			}
			else{
				chdir(words[1]);
			}
		}

		// exiting
		else if((!strcmp(words[0], "exit")) || (!strcmp(words[0], "quit"))){
			return EXIT_SUCCESS;
		}

		// undefined command
		else{
			printf("myshell: Unknown command: %s\n",words[0]);
		}
	}
	return EXIT_SUCCESS;
}


void signalHandler(int signum){
	return;
}

int start_p(char *words[], char **newwords, int i){
	pid_t pid = fork();
	sleep(1);
	if(pid == 0){ // child process
		if(execvp(words[i],newwords) == -1){
			printf("myshell: Failed to exec: %s\n", strerror(errno));
			return -1;
		}
	} else if(pid == -1){
		printf("myshell: Failed to fork: %s\n", strerror(errno));
		return -1;
	} 
	return pid;
}

void wait_p(int pid){
	int status;
	pid_t wpid = waitpid(pid,&status,0);
	if(wpid == -1){
		printf("myshell: Failed to wait: %s\n", strerror(errno));
	} else{ 
		int correctexit = WIFEXITED(status);

		if(correctexit){
			int exitstat = WEXITSTATUS(status);
			printf("myshell: Process %d exited normally with status %d\n", wpid, exitstat);
		}
		else if(WCOREDUMP(status)){
			printf("myshell: Process %d exited because of a core dump\n", wpid);
		}
		else if(WIFSIGNALED(status)){
			printf("myshell: Process %d exited because of a signal: %s\n", wpid, strsignal(WTERMSIG(status)));
		}
		else{
			printf("myshell: Process %d exited abnormally\n", wpid);
		}
	}
	return;
}
