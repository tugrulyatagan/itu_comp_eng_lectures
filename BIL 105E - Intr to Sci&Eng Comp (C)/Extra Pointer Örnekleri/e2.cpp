//  Traversing an array with as pointer

#include <iostream>
using namespace std;

int main()
{ const int SIZE = 3;
  short a[SIZE] = {22, 33, 44};
  cout << "a = " << a << endl;
  cout << "sizeof(short) = " << sizeof(short) << endl;
  short* end = a + SIZE;       // converts SIZE to offset 6
  short sum = 0;
  for (short* p = a; p < end; p++)
  { sum += *p;
    cout << "\t p = " << p;
    cout << "\t *p = " << *p;
    cout << "\t sum = " << sum << endl;
  }
  cout << "end = " << end << endl;
}
