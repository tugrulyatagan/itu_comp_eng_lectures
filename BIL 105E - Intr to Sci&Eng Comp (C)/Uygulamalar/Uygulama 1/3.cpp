/*********************************************
* ornek   : 1-3                              *
* aciklama: define ile toplama ornegi        *
* derleme : g++ -o program_ismi 3.cpp        *
*********************************************/

#include <iostream>
#define ARTI 5+3

using namespace std;
int main()
{	
  int x = 5, y = 2, z;

  z = ARTI; //toplama islemi bu satirda
  cout << "x + y = " << z << "\n";

  return 0;
}
