// e12_6.cpp
// http://www.buzluca.info/oop
//  demonstrates reverse(), merge(), and unique() **/
#include <iostream>
#include <list> 
using namespace std;

int main()
{
   int arr1[] = { 40, 30, 20, 10 };
   int arr2[] = { 15, 20, 25, 30, 35 };

   list<int> list1(arr1, arr1+4);
   list<int> list2(arr2, arr2+5);

   list1.reverse();                     // reverse list1: 10 20 30 40
   list1.merge(list2);                  // merge list2 into list1
   list1.unique();                      // remove duplicate 20 and 30
   int size = list1.size();
   for(int j=0; j<size; j++)            // for every item
   {
      cout << list1.front() << ' ';     // read item from front
      list1.pop_front();                // pop item off front
   }
   return 0;
}
/*
The first list is in backward order, so I return it to normal sorted order using the reverse()
member function. (It’s quick to reverse a list container because both ends are accessible.)
This is necessary because the second member function, merge(), operates on two lists and
requires both of them to be in sorted order. Following the reversal, the two lists are
10, 20, 30, 40
15, 20, 25, 30, 35

Now the merge() function merges list2 into list1, keeping everything sorted and expanding
list1 to hold the new items. The resulting content of list1 is
10, 15, 20, 20, 25, 30, 30, 35, 40

Finally, I apply the unique() member function to list1. This function finds adjacent pairs
of elements with the same value and removes all but the first. The contents of list1 are then displayed. The output of LISTPLUS is
10, 15, 20, 25, 30, 35, 40

To display the contents of the list, I use the front() and pop_front() member functions
in a for loop. Each element, from front to back, is displayed and then popped off the list.
The process of displaying the list destroys it. This may not always be what you want,
but at the moment it’s the only way you have learned to access successive list elements. Iterators, described in the next session, will solve this problem.
*/