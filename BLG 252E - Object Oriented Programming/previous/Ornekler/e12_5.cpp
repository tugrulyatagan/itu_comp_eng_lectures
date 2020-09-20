// e12_5.cpp
// http://www.buzluca.info/oop
// demonstrates push_front(), front(), pop_front() 
#include <iostream>
#include <list>
using namespace std;

int main()
{
   list<int> ilist;
   ilist.push_back(30);                 // push items on back
   ilist.push_back(40);
   ilist.push_front(20);                // push items on front
   ilist.push_front(10);

   int size = ilist.size();             // number of items

   for(int j=0; j<size; j++)
   {
      cout << ilist.front() << ' ';     // read item from front
      ilist.pop_front();                // pop item off front
   }
   return 0;
}
/*
The push_front(), pop_front(), and front() member functions are similar to push_back(),
pop_back(), and back(), which you’ve already seen at work with vectors.
Note that you can’t use random access for list elements because such access is too slow;
that is, the [] operator is not defined for lists. If it were, this operator would need to
traverse along the list, counting elements as it went, until it reached the correct one,
a time-consuming operation. If you need random access, you should use a vector or a deque.
*/