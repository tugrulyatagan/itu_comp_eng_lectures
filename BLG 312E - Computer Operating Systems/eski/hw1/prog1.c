#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (void)
{
  pid_t f;

  f=fork();
  if (f==-1)
  {
    printf("Hata \n");
    exit(1);
  } 
  else if (f==0)
  {
    printf("   Cocuk: Proses Kimlik numaram: %d \n", getpid());
    sleep(1);
    printf("   Cocuk: Annemin proses kimlik numarasi %d \n", getppid());
    exit(0);
  }
  else
  {
    printf("Anne: Proses Kimlik Numaram: %d \n", getpid());
    printf("Anne: Cocugumun Proses Kimlik Numarasi: %d \n", f);
    wait(NULL);
    printf("Anne: Sonlaniyorum...\n");
    exit(0);
  }
  return (0);
}

