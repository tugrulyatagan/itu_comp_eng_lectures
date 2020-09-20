/*********************************************
* ornek   : 1-4                              *
* aciklama: matematik kutuphanesi kullanimi  *
* derleme : g++ -lm -o program_ismi 4.cpp    *
*********************************************/

#include <iostream>
#include <cmath>
#include <iomanip>  // library for formatting io functions

using namespace std;
int main()
{
  float x = 25;
  double y;
  y = pow(x,2);
  cout << "y = " << fixed << setw(20) << setprecision(2) << right << y << "\n";
  // fixed    : displaying float number with dotted form (like XXX.yyy)
  // setw(20) : total width of output stream
  // setprecision(2) : displaying size after dot(.)
  // right : align output stream right
  
  // printf("%20.2f", y);  // stdio.h library must be included.
  return 0;
}
