//  Using pointer variables

#include <iostream>
using namespace std;

int main()
{ int n=44;  // n holds the int 44
  cout << "int n=44;  // n holds the int 44:\n";
  cout << "\t\t    n = " << n << endl;
  cout << "\t\t   &n = " << &n << endl;
  int* pn=&n;  // pn holds the address of n
  cout << "int* pn=&n;  // pn holds the address of n:\n";
  cout << "\t\t    n = " << n << endl;
  cout << "\t\t   &n = " << &n << endl;
  cout << "\t\t   pn = " << pn << endl;
  cout << "\t\t  &pn = " << &pn << endl;
  cout << "\t\t  *pn = " << *pn << endl;
  *pn = 77;  // changes the value of n to 77
  cout << "*pn = 77;  // changes the value of n to 77:\n";
  cout << "\t\t    n = " << n << endl;
  cout << "\t\t   &n = " << &n << endl;
  cout << "\t\t   pn = " << pn << endl;
  cout << "\t\t  &pn = " << &pn << endl;
  cout << "\t\t  *pn = " << *pn << endl;
  int* q=&n;  // q also holds the address of n
  cout << "int* q=&n;  // q also holds the address of n:\n";
  cout << "\t\t    n = " << n << endl;
  cout << "\t\t   &n = " << &n << endl;
  cout << "\t\t   pn = " << pn << endl;
  cout << "\t\t  &pn = " << &pn << endl;
  cout << "\t\t  *pn = " << *pn << endl;
  cout << "\t\t    q = " << q << endl;
  cout << "\t\t   &q = " << &q << endl;
  cout << "\t\t   *q = " << *q << endl;
}
