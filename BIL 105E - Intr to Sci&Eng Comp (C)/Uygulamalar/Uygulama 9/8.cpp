/************************************************************************
*																		*
* ders 9 ornekleri									                    *
*                                                                       *
* 														                *
* derlemek icin g++ -o program_ismi 8.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;
int main() {
	
  float *new1, *new2;
  int i;
  
  new1= new float[3];
  new2= new float[3];
  
if(new1!=NULL && new2!=NULL) {

    for(i=0 ; i<3 ; i++) {
      cout<<"new1["<<i<<"] holds "<<new1[i]<<endl;
      cout<<"new2["<<i<<"] holds "<<*(new2+i)<<endl;
     
    }
   delete new1;
   delete new2;

    return 0;
  }
  else {
    cout<<"Not enough memory\n";
    return 1;
  }
}
