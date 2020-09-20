//  Using dynamic arrays

#include <iostream>
using namespace std;
void get(double*&,int&);
void print(double*,int);

int main()
{ double* a;    // a is simply an unallocated pointer
  int n;
  get(a,n);     // now a is an array of n doubles
  print(a,n);
  delete [] a;  // now a is simply an unallocated pointer again
  get(a,n);     // now a is an array of n doubles
  print(a,n);
}

void get(double*& a, int& n)
{ cout << "Enter number of items: ";  cin >> n;
  a = new double[n];
  cout << "Enter " << n << " items, one per line:\n";
  for (int i = 0; i < n; i++)
  { cout << "\t" << i+1 << ": ";
    cin >> a[i];
  }
}

void print(double* a, int n)
{ for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;
}
