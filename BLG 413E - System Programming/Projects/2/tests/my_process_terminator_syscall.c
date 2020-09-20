#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define NR_mycall 351

int main (int argc, char **argv){
	if (argc != 3){
		printf("Wrong parameters\n");
		return 0;
	}
	pid_t pid = (pid_t) atoi(argv[1]);
	int flag = atoi(argv[2]);
	long y = syscall(NR_mycall, pid, flag);
	printf("%s\n", strerror(y));
	return 0;
}
