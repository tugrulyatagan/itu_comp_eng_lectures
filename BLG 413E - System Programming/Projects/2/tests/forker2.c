#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char **argv)
{
	if (argc != 2){
		printf("Wrong parameters\n");
		return 0;
	}
	int i;
	pid_t parent = getpid();
	printf("Parent process %d\n",parent);
    
	for (i = 0; i < 4; i++){
		if(fork() == 0){ // child process
			//printf("Child Proces %d with parent %d\n",getpid(),getppid());
		}
	}
	if (parent == getpid()){
		pid_t pid = getpid();
		int which = PRIO_PROCESS;
		int n = atoi(argv[1]);
		nice(n);
		int priority = getpriority(which,pid);
		printf("Parent pid: %d\n",pid);
		printf("Parent priority: %d\n",priority);
		char command[25];
		sprintf(command, "pstree -p %d", parent);
		system(command);
		exit(EXIT_SUCCESS);
	}
	pause();
	exit(EXIT_SUCCESS);
} 
