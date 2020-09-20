// e12_7.cpp
// http://www.buzluca.info/oop
// demonstrates push_back(), push_front(), front() /
#include <iostream>
#include <deque>
using namespace std;

int main()
{
   deque<int> deq;

   deq.push_back(30);                   // push items on back
   deq.push_back(40);
   deq.push_back(50);
   deq.push_front(20);                 // push items on front
   deq.push_front(10);

   deq[2] = 33;                        // change middle item

   for(int j=0; j<deq.size(); j++)
      cout << deq[j] << ' ';           // display items
   return 0;
}
/*
You’ve already seen examples of push_back(), push_front(), and operator []. 
They work the same for deques as for other containers. The output of this program is
10 20
*/
