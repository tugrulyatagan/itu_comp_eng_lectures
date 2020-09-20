#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	int i,j,k, status;
	pid_t grandParent = getpid();
	printf("Parent process %d\n",grandParent);
    
	for (i = 0; i < 4; i++){
		if(fork() == 0){ // child process
			for (j = 0; j < 3; j++){
				if(fork() == 0){ // grandChild process
					for (k = 0; k < 2; k++){
						if(fork() == 0){ // grandGrandChild process
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	
	
	if (grandParent == getpid()){
		sleep(1);
		char command[25];
		sprintf(command, "pstree -p %d", grandParent);
		system(command);
	}
	
	for (i = 0; i < 24; i++){
		waitpid(0,&status,0);
	}
	pause();
	exit(EXIT_SUCCESS);
} 
