/************************************************************************
*																		*
* ders 9 ornekleri 								                     	*
* Dynamic Memory Allocation											    *
* derlemek icin g++ -o program_ismi 9.cpp								*
*																		*
************************************************************************/

#include <iostream>
using namespace std;
int main() {
  int *ptr;
  int i;

  ptr=new int[5];
  //ptr = calloc(5, sizeof(int));

  if(ptr!=NULL) {
    *ptr = 1;
    *(ptr + 1) = 2;
    ptr[2] = 4;
    ptr[3] = 8;
    ptr[4] = 16;
    /*ptr[5] = 32; wouldn't assign anything */

    delete ptr;
   // ptr = realloc(ptr, 7*sizeof(int));
    ptr=new int[7];

    if(ptr!=NULL) {
     cout<<"Now allocating more memory... \n";
      ptr[5] = 32; /* now it's legal! */
      ptr[6] = 64;

      for(i=0 ; i<7 ; i++) {
        cout<<"ptr["<<i<<"] holds "<<ptr[i]<<endl;
      }
     delete ptr;
     // realloc(ptr,0); /* same as free(ptr); - just fancier! */
      return 0;
    }
    else {
      cout<<"Not enough memory - realloc failed.\n";
      return 1;
    }
  }
  else {
      cout<<"Not enough memory - calloc failed.\n";
    return 1;
  }
}

