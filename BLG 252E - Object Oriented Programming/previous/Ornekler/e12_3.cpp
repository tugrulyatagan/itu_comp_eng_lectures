// e12_3.cpp
// http://www.buzluca.info/oop
// demonstrates constructors, swap(), empty(), back(), pop_back() **/
#include <iostream>
#include <vector>
using namespace std;

int main()
{                                            // an array of floats
   float arr[] = { 1.1, 2.2, 3.3, 4.4 };
   vector<float> v1(arr, arr+4);             // initialize vector to array
   vector<float> v2(4);                      // empty vector of size 4

   v1.swap(v2);                              // swap contents of v1 and v2

   while( !v2.empty() )                      // until vector is empty,
      {
      cout << v2.back() << ' ';              // display the last element
      v2.pop_back();                         // remove the last element
      }                                      // output: 4.4 3.3 2.2 1.1
   return 0;
}
/*
I’ve used two new vector constructors in this program. The first initializes the vector v1
with the values of a normal C++ array passed to it as an argument.
The arguments to this constructor are pointers to the start of the array and
to the element one past the end. The second constructor sets v2 to an initial size of 4,
but does not supply any initial values. Both vectors hold type float.
The swap() member function exchanges all the data in one vector with all the data in another,
keeping the elements in the same order. In this program, only garbage data is in v2,
so it’s swapped with the data in v1. I display v2 to show it now contains the data that was in v1.
The output is
4.4, 3.3, 2.2, 1.1

The back() member function returns the value of the last element in the vector.
I display this value with cout. The pop_back() member function removes the last element in the vector.
Thus, each time through the loop there is a different last element.
It’s a little surprising that pop_back() does not simultaneously return the value of the last element
and remove it from the vector, as you’ve seen in previous examples with stacks,
but it doesn’t, so back() must be used as well.)
*/
