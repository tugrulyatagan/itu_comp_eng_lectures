//e12_13.cpp
// http://www.buzluca.info/oop
// set stores string objects
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{                               // array of string objects
   string names[] = {"Katie", "Robert",
                     "Mary", "Amanda", "Marie"};           
   set<string> nameSet(names, names+5);// initialize set to array
                                    
   set<string>::const_iterator iter;  // iterator to set
   nameSet.insert("Jack");            // insert some more names
   nameSet.insert("Larry");
   nameSet.insert("Robert");          // no effect; already in set
   nameSet.insert("Barry");
   nameSet.erase("Mary");              // erase a name
                                       // display size of set
   cout << "\nSize=" << nameSet.size() << endl;
   iter = nameSet.begin();             // display members of set
   while( iter != nameSet.end() )
      cout << *iter++ << '\n';

   string searchName;                  // get name from user
   cout << "\nEnter name to search for: ";
   cin >> searchName;
                                   // find matching name in set

   iter = nameSet.find(searchName);
   if( iter == nameSet.end() )
      cout << "The name " << searchName << " is NOT in the set.";
   else
      cout << "The name " << *iter << " IS in the set."; 
   return 0;
}
