// e12_4.cpp
// http://www.buzluca.info/oop
//demonstrates insert(), erase() **/
#include <iostream>
#include <vector>
using namespace std;

int main()
{
   int arr[] = { 100, 110, 120, 130 };  // an array of ints
   vector<int> v(arr, arr+4);           // initialize vector to array
   int j;
   cout << "\nBefore insertion: ";
   for(j=0; j<v.size(); j++)            // display all elements
      cout << v[j] << ' ';

   v.insert( v.begin()+2, 115);         // insert 115 at element 2
   cout << "\nAfter insertion:  ";
   for(j=0; j<v.size(); j++)            // display all elements
      cout << v[j] << ' ';

   v.erase( v.begin()+2 );              // erase element 2

   cout << "\nAfter erasure:    ";
   for(j=0; j<v.size(); j++)            // display all elements
      cout << v[j] << ' ';
   return 0;
}
/*
The insert() member function (this version of it) takes two arguments: 
the place where an element will be inserted in a container and the value of the element.
I add 2 to the begin() member function to specify element 2 (the third element) in the vector.
The elements from the insertion point to the end of the container are moved upward
to make room and the size of the container is increased by 1.

The erase() member function removes the element at the specified location.
The elements above the deletion point are moved downward and the size of the container
is decreased by 1. Here’s the output from VECTINS:

Before insertion: 100 110 120 130
After insertion:  100 110 115 120 130
After erasure:    100 110 120 130
*/
