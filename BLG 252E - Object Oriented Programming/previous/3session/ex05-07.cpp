// Illustrating the generic for_each algorithm
#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>
using namespace std;

void print_list(string s)
{
  cout << s << endl;
}

int main()
{
  cout << "Illustrating the generic for_each algorithm." 
       << endl;
  list<string> dlist;
  dlist.insert(dlist.end(), "Clark");
  dlist.insert(dlist.end(), "Rindt");
  dlist.insert(dlist.end(), "Senna");

  // Print out each list element:
  for_each(dlist.begin(), dlist.end(), print_list);
  return 0;
}
