/************************************************************************
*																		*
* ders 9 ornekleri - Deniz Demiray										*
* irc.essex.ac.uk/www.iota-six.co.uk/c/f7_dynamic_memory_allocation.asp *
* malloc / calloc														*
* derlemek icin gcc -o program_ismi 8.c									*
*																		*
************************************************************************/

#include <stdio.h>
#include <stdlib.h> 

int main() {
	
  float *calloc1, *calloc2, *malloc1, *malloc2;
  int i;

  calloc1 = calloc(3, sizeof(float)); /* might need to cast */ 
  calloc2 = calloc(3, sizeof(float));
  malloc1 = malloc(3 * sizeof(float));
  malloc2 = malloc(3 * sizeof(float));

if(calloc1!=NULL && calloc2!=NULL && malloc1!=NULL && malloc2!=NULL) {

    for(i=0 ; i<3 ; i++) {
      printf("calloc1[%d] holds %05.5f, ", i, calloc1[i]);
      printf("malloc1[%d] holds %05.5f\n", i, malloc1[i]);
      printf("calloc2[%d] holds %05.5f, ", i, *(calloc2 + i));
      printf("malloc2[%d] holds %05.5f\n", i, *(malloc2 + i));
    }

    free(calloc1);
    free(calloc2);
    free(malloc1);
    free(malloc2);

    return 0;
  }
  else {
    printf("Not enough memory\n");
    return 1;
  }
}
