// Illustrating the stack adaptor.
#include <iostream>
#include <stack>
using namespace std;

int main()
{
  cout << "Illustrating the stack adaptor." << endl;
  int thedata[] = {45, 34, 56, 27, 71, 50, 62};
  stack<int> s;
  cout << "The stack size is now " << s.size() << endl;
  int i;
  cout << "Pushing 4 elements " << endl;
  for (i = 0; i < 4; ++i)
    s.push(thedata[i]);
  cout << "The stack size is now " << s.size() << endl;
  cout << "Popping 3 elements " << endl;
  for (i = 0; i < 3; ++i) {
    cout << s.top() << endl;
    s.pop();
  }
  cout << "The stack size is now " << s.size() << endl;
  cout << "Pushing 3 elements " << endl;
  for(i = 4; i < 7; ++i)
    s.push(thedata[i]);
  cout << "The stack size is now " << s.size() << endl;
  cout << "Popping all elements" << endl;
  while (!s.empty()) {
    cout << s.top() << endl;
    s.pop();
  } 
  cout << "The stack size is now " << s.size() << endl;
  return 0;
}
