// Illustrating the queue adaptor.
#include <iostream>
#include <queue> 
#include <list>
using namespace std;

int main()
{
  cout << "Illustrating the queue adaptor." << endl;
  int thedata[] = {45, 34, 56, 27, 71, 50, 62};
  queue<int, list<int> > q;  
  cout << "The queue size is now " << q.size() << endl;
  int i;
  cout << "Pushing 4 elements " << endl;
  for (i = 0; i < 4; ++i)
    q.push(thedata[i]);
  cout << "The queue size is now " << q.size() << endl;
  cout << "Popping 3 elements " << endl;
  for (i = 0; i < 3; ++i) {
    cout << q.front() << endl;
    q.pop();
  }
  cout << "The queue size is now " << q.size() << endl;
  cout << "Pushing 3 elements " << endl;
  for(i = 4; i < 7; ++i)
    q.push(thedata[i]);
  cout << "The queue size is now " << q.size() << endl;
  cout << "Popping all elements" << endl;
  while (!q.empty()) {
    cout << q.front() << endl;
    q.pop();
  } 
  cout << "The queue size is now " << q.size() << endl;
  return 0;
}
