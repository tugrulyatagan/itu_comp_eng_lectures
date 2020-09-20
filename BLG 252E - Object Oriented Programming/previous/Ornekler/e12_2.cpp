// e12_2.cpp
// http://www.buzluca.info/oop
//    demonstrates push_back(), operator[], size() **/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
   vector<int> v;                   // create a vector of ints

   v.push_back(10);                 // put values at end of array
   v.push_back(11);
   v.push_back(12);
   v.push_back(13);

   v[0] = 20;                       // replace with new values
   v[3] = 23;

   for(int j=0; j<v.size(); j++)    // display vector contents
     cout << v[j] << ' ';
   return 0;
}
/*
I use the vector’s default (no-argument) constructor to create a vector v.
As with all STL containers, the template format is used to specify the type of variable the container will hold; in this case, type int.
I don’t specify the container’s size, so it starts off at 0.
The push_back() member function inserts the value of its argument at the back of the vector.
(The back is where the element with the highest index number is.)
The front of a vector (where the element with index 0 is), unlike that of a list or queue,
is not accessible.
Here I push the values 10, 11, 12, and 13, so that v[0] contains 10, v[1] contains 11,
v[2] contains 12, and v[3] contains 13.

Once a vector has some data in it, this data can be accessed-both read and written to-using
the overloaded [] operator, just as if it were in an array. I use this operator to change
the first element from 10 to 20 and the last element from 13 to 23.
Here’s the output from VECTOR:
20 11 12 23
*/
