// Using the generic accumulate algorithm to compute a product,
// using a function object
#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>  // For accumulate
using namespace std; 

class multiply {
 public:
  int operator()(int x, int y) const { return x * y; }
};

int main()
{
  cout << "Using generic accumulate algorithm to "
       << "compute a product." << endl;

  int x[5] = {2, 3, 5, 7, 11};

  // Initialize vector1 to x[0] through x[4]:
  vector<int> vector1(&x[0], &x[5]); 
  
  int product = accumulate(vector1.begin(), vector1.end(), 1, multiply());
    
  assert (product == 2310);
  cout << " --- Ok." << endl;
  return 0;
}
