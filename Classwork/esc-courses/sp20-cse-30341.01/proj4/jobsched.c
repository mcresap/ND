#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <complex.h>
#include <pthread.h>
#include <sys/stat.h>

//global
typedef struct job {
	int jobid ;
	int noc; //# of commands
	pid_t pid;
	char state[30];
	int exit_status;
	char **cmds;
	char filename[526];
	struct job *next;
} job;

typedef struct linkedlist{
	struct job *head;
} linkedlist;

char * PROGRAM = "jobsched";
int BUFFER_LENGTH = 1024;
pthread_mutex_t mutex;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int njobs = 1; //one by default
int jobid = 1;
linkedlist * jobq; //job queue

//functions 
void usage();
void parse(char **, int);
void call_submit(char ** command, int nwords);
void call_status();
void call_wait(int jobid);
void call_remove(int jobid);
void call_njobs(int n);
void call_drain();
int currunning();

void setjobs(int n){ //set n jobs
	pthread_mutex_lock(&mutex);
	njobs = n;
	pthread_mutex_unlock(&mutex);
}
int getjobs(){	
	return njobs;
}
job * create_job(){	 
	job * ajob = malloc(sizeof(job));
	if(ajob == NULL){
		printf("%s: Malloc failed.", PROGRAM);
		exit(1);
	}
	sprintf(&(ajob->state[0]), "%s", "WAIT");
	ajob->jobid = 0;
	ajob->exit_status = 666;
	ajob->noc = 0;
	sprintf(&(ajob->filename[0]), "%s", "output.jobid");
	ajob->next = NULL;
	ajob->pid = -3;
	return ajob;
}
struct job * dequeue(){	
	pthread_mutex_lock(&mutex);
	while(jobq->head == NULL){
		pthread_cond_wait(&cond, &mutex);
	}
	job * retjob = NULL;
	while(retjob == NULL){
		for(job * job1 = jobq->head; job1 != NULL; job1 =job1->next){
			if(strcmp(job1->state, "WAIT") == 0){
				retjob = job1;
				pthread_mutex_unlock(&mutex);
				return retjob;
			}
		}
		pthread_cond_wait(&cond, &mutex); //wait for job to be added to queue
	}
	return NULL;
}
		
void wait_handler(int sign, siginfo_t * siginfo, void *context){
	if(sign == SIGCHLD){
		int status;
		if((waitpid(siginfo->si_pid, &status, 0))<0){
			printf("%s: waitpid has failed\n", PROGRAM);
			exit(1);
		}
		job * runjob = jobq->head;	//initialize head of queue
		while(runjob != NULL){
			if(runjob->pid == siginfo->si_pid){
				break;
			}
			runjob = runjob->next;
		}
		pthread_mutex_lock(&mutex);
		runjob->exit_status = status;
		sprintf(&(runjob->state[0]), "%s", "DONE");
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex);
	}
}
		
void run_job(struct job * runjob){
	pid_t pid = fork();
	pthread_mutex_lock(&mutex);
	runjob->pid = pid;
	pthread_mutex_unlock(&mutex);

	if(pid < 0){
		printf("%s: Fork failed %s\n", PROGRAM, strerror(errno));
		exit(1);
	}
	else if(pid > 0){
		pthread_mutex_lock(&mutex);
		sprintf(&(runjob->state[0]), "%s", "RUN"); //parent updates status
		pthread_mutex_unlock(&mutex); 

		struct sigaction newact;
		newact.sa_sigaction = wait_handler;
		sigemptyset(&newact.sa_mask);
		newact.sa_flags = SA_SIGINFO;
		if((sigaction(SIGCHLD, &newact, NULL)) < 0){
			printf("%s: Sigaction failed", PROGRAM);
		}
	}
	else{ 
		int fd = open(runjob->filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd > 0){
			printf("%s: Failed to open file %s\n", PROGRAM, strerror(errno));
			exit(1);
		}
		if(dup2(fd, 1) < 0){ 
			printf("%s: Failed t o redirect output: %s\n", PROGRAM, strerror(errno));
		}
		close(fd);
		execvp(runjob->cmds[0], runjob->cmds);
		printf("%s: EXEC failed: %s\n", PROGRAM, strerror(errno));
		exit(1);
	}
}

void sched_handler(){
	while(1){
		int n = getjobs();
		int i = currunning();
		while(i < n){
			job * runjob = dequeue();
			run_job(runjob);
			i = i+1;
		}
	}
}

int main(int argc, char *argv[]){
	if(argc < 1){
		printf("%s: invalid args\n", PROGRAM);
		usage();
		exit(1);
	}
	
	jobq = malloc(sizeof (linkedlist));
	char line[BUFFER_LENGTH];
	char * words[100];
	int nwords;
	pthread_mutex_init(&mutex, 0);
	pthread_t sched_thread;
	if(pthread_create(&sched_thread, 0, (void *) sched_handler, 0 ) != 0){
		printf("Error creating thread");
		exit(1);
	}

	jobq->head = NULL; //initialize head
	while(1){
		printf("%s> ", PROGRAM);
		if(!fgets(line, BUFFER_LENGTH, stdin)){ 
			printf("%s: failed to get line: %s\n", PROGRAM, strerror(errno));
			exit(1); //if fgets fails
		}
		size_t length = strlen(line); 
		if(line[length - 1] == '\n'){
			line[length - 1] = '\0';
		}
		int i = 0; //get rid of the white space
		while(isspace(line[i])){
			line[i] = line[i+1];
			i++;
		}
		if(strcmp(line, "quit")==0){
			exit(1);
		}
		else if(strcmp(line, "help")==0){
			usage();
			continue;
		}
		else if (line[0] == '\0'){ //check for blank line
			continue;
		}
		else{
			char * token = strtok(line, " \t\n");
			int i = 0;
			while(token != NULL){
				words[i] = token;
				token = strtok(NULL, " \t\n");
				i++;
			}
			words[i] = NULL; //for execvp
			nwords = i;
		
			parse(words, nwords);
		}
	}

	if(pthread_join(sched_thread, NULL)){
		printf("Error joining thread.\n");
		exit(1);
	}
	return 0;
}

void usage(){ //help list
	printf("Use: jobsched [command]\n");
	printf("Where commands are:\n");
	printf("submit <command>	where the submit command defines a new job and the Unix command that should be run\n");
	printf("status				where the status command lists all of the jobs currently known\n");
	printf("wait <jobid>		where the wait command takes a jobid and pauses until that job is done executing\n");
	printf("remove <jobid>		where the remove command takes a jobid and then removes it from the queue, deleting any stored output of the job - only done if job is in a WAIT or DONE state\n");
	printf("njobs <n>			indicates how may jobs the scheculer may run at once\n");
	printf("drain				waits until all jobs in the queue are in the DONE state\n");
	printf("quit				exits the program\n");
	printf("help				displays available commanfs\n");
}

void parse(char ** words, int nwords){
	if((strcmp(words[0], "submit")) == 0){
		if(nwords != 2){
			usage();
			return;
		}
		call_submit(words + 1, nwords - 1);
	}
	else if((strcmp(words[0], "status")) == 0){
		if(nwords != 1){
			usage();
			return;
		}
		call_status();
	}
	else if((strcmp(words[0], "wait")) == 0){
		if(nwords != 2){
			usage();
			return;
		}
		int jobid = atoi(words[1]);
		if(jobid != 0) 
			call_wait(jobid);
	}
	else if((strcmp(words[0], "remove")) == 0){
		if(nwords != 2){
			usage();
			return;
		}
		int jobid = atoi(words[1]);
		if(jobid != 0) 
			call_remove(jobid);
	}
	else if((strcmp(words[0], "njobs")) == 0){
		if(nwords > 2){
			usage();
			return;
		}
		int n = 1;
		if (words[1])
			n = atoi(words[1]);
		if(n != 0) 
			call_njobs(n);
	}
	else if((strcmp(words[0], "drain")) == 0){
		if(nwords != 1){
			usage();
			return;
		}
		call_drain();
	}
	else{
		printf("%s: unknown command: %s\n", PROGRAM, words[0]);
		usage();
		return;
	}
}

void call_submit(char ** words, int nwords){
	pthread_mutex_lock(&mutex);	//lock thread
	job * ajob = create_job();	//initialize v 
	ajob->jobid = jobid;
	
	ajob->cmds = malloc((nwords + 1)*sizeof(char*));
	for (int i = 0; i < nwords; ++i){
		ajob->cmds[i] = strdup(words[i]);
	}
	ajob->cmds[nwords] = NULL;
	ajob->noc = nwords;

	sprintf(&(ajob->filename[0]), "%s%d", "output.", ajob->jobid);
	ajob->next = jobq->head;
	jobq->head = ajob;
	if(jobq->head != NULL){ //if list is empty wake up the scheduled thread
		pthread_cond_broadcast(&cond);
	}
	jobid = jobid + 1;

	
	printf("Job submitted: job id = %d\n", ajob->jobid);
	pthread_mutex_unlock(&mutex);
}

void call_status(){
	pthread_mutex_lock(&mutex); //don't want multiple threads editing at once
	char command_str[200];
	printf("JOBID	STATE	EXIT	COMMAND\n");
	job * job1 = jobq->head;

	while(job1 != NULL){
		char *first = job1->cmds[0];
		strcpy(command_str, first);
		if(job1->noc > 1){
			for (int j = 1; j < job1->noc; j++){
				strcat(command_str, " ");
				strcat(command_str, job1->cmds[j]);
	 		}
		}
		if (job1->exit_status == 666){
			printf("%d	%s	-	%s\n", job1->jobid, job1->state, command_str);
		}
		else{
			printf("%d	%s	%d	%s\n", job1->jobid, job1->state, job1->exit_status, command_str);
		}
		job1 = job1->next;
	}
	pthread_mutex_unlock(&mutex);
}

void call_wait(int jobid){
	pthread_mutex_lock(&mutex); //want scheduled thread to alert main thread
	job * waitjob;
	int flag = 0; //check to see if job was found
	job * job1 = jobq->head;
	
	while(job1 != NULL){	
		if (job1->jobid == jobid){
			waitjob = job1;
			flag = 1;
			break;
		}	
		job1 = job1->next;
	}

	if (!flag){
		printf("invalid job id\n");
		pthread_mutex_unlock(&mutex);
		return;
	}
	while((strcmp(waitjob->state, "WAIT") == 0) || (strcmp(waitjob->state, "RUN") == 0)){
		pthread_cond_wait(&cond, &mutex);
	}
	
	if((strcmp(waitjob->state, "DONE") == 0)){
		char command_str[200];
		char *first = waitjob->cmds[0];
		
		strcpy(command_str, first);
		if(job1->noc > 1){
			for (int j = 1; j < job1->noc; j++){
				strcat(command_str, waitjob->cmds[j]);
			}
		}
		printf("Job ID: %d Commands: %s\n", waitjob->jobid, command_str);
		FILE *fd = fopen(waitjob->filename, "r");
		if (fd == NULL){
			printf("File does not exist/no stdout %s\n", waitjob->filename);
			exit(1);
		}
		char c = fgetc(fd); //get char from stream to iterate
		while (c != EOF){	
			printf("%c", c);
			c = fgetc(fd);
		}
		fclose(fd);
	}
	pthread_mutex_unlock(&mutex);
}

void call_remove(int jobid){
	pthread_mutex_lock(&mutex);
	job * waitjob = NULL;
	for (job* job1 = jobq->head; job1 != NULL; job1 = job1->next){
		if(job1->jobid == jobid){
			waitjob = job1;
			break;
		}
	}
	if(waitjob == NULL){
		printf("invalid job id\n");
		pthread_mutex_unlock(&mutex);
		return;
	}
	if(strcmp(waitjob->state, "RUN") == 0){
		printf("job is currently running and cannot remove job from queue\n");
	}
	else if((strcmp(waitjob->state, "WAIT") == 0) || ((strcmp(waitjob->state, "DONE") ==0))){
		job * cur = jobq->head;	
		job * temp = waitjob->next;
		if(jobq->head == waitjob){
			jobq->head = waitjob->next;
		}
		else{
			while(cur->next != waitjob){
				cur = cur->next;
			}
			cur->next = temp;
		}
		if(remove(waitjob->filename) != 0){
			printf("unable to delete file: %s\n", waitjob->filename);
		}
		free(waitjob);
	}
	pthread_mutex_unlock(&mutex);
}

void call_njobs(int n){ 
	setjobs(n);
}

void call_drain(){
	pthread_mutex_lock(&mutex);
	while(currunning()){ //wait until all jobs in list are done
		pthread_cond_wait(&cond, &mutex); //use a condition so don't wake up until all jobs are done
	}
	pthread_mutex_unlock(&mutex);
}

int currunning(){
	int currunning = 0;
	for(job* job1 = jobq->head; job1 != NULL; job1 = job1->next){
		if(strcmp(job1->state, "RUN") == 0){
			currunning = currunning + 1;
		}
	}
	return currunning;
}

