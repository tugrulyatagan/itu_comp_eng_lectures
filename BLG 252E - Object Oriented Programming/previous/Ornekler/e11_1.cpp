// e11_1.cpp
// http://www.buzluca.info/oop
//	 template used for absolute value function **/
#include <iostream>
using namespace std;

template <class T>      // function template
T abs(T n)
{
	return (n < 0) ? -n : n;
}

int main()
{ 
  int int1 = 5; 
  int int2 = -6; 
  long lon1 = 70000L; 
  long lon2 = -80000L; 
  double dub1 = 9.95; 
  double dub2 = -10.15; 
  // calls instantiate functions
  cout << "abs(" << int1 << ")=" << abs(int1) << endl;       // abs(int) 
  cout << "abs(" << int2 << ")=" << abs(int2) << endl;       // abs(int) 
  cout << "abs(" << lon1 << ")=" << abs(lon1) << endl;     // abs(long) 
  cout << "abs(" << lon2 << ")=" << abs(lon2) << endl;     // abs(long) 
  cout << "abs(" << dub1 << ")=" << abs(dub1) << endl;   // abs(double) 
  cout << "abs(" << dub2 << ")=" << abs(dub2) << endl;   // abs(double) 
  return 0;
} 
