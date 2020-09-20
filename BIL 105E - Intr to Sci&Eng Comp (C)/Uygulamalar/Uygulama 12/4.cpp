// modify basefield
#include <iostream>
using namespace std;

int main () {
  double a,b,c;
  a = 3.1415926534;
  b = 2006.0;
  c = 1.0e-10;
  cout.precision(5);
  cout       <<         a << '\t' << b << '\t' << c << endl;
  cout <<   fixed    << a << '\t' << b << '\t' << c << endl;
  cout << scientific << a << '\t' << b << '\t' << c << endl;
  return 0;
}
