#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int tmp=0;

void my_function(int count) {
   tmp=tmp+1;
   printf("%d: Value= %d\n", count, tmp);
   exit(0);
}

int main(void)
{
  int f=1, i;

  for (i=0; i<3; i++) {
    if (f>0){
      f=fork();
      wait(NULL);
    }
    if (f==-1) {
      printf("fork error....\n");
      exit(-1);
    }
    if (f==0)
      break;
  }
  if (f == 0) {
     my_function(i);
  }
  else {
    printf("Main: Created %d procs.\n", i);
    exit(0);
  }
  return 0;
}
