// e12_14.cpp
// http://www.buzluca.info/oop
// tests ranges within a set 
#include <iostream>
#include <set>
#include <string>         
using namespace std;

int main()
{                             // set of string objects
   set<string> city;
                                 // iterator to set
   set<string>::iterator iter;

   city.insert("Trabzon");     // insert city names
   city.insert("Adana");
   city.insert("Edirne");
   city.insert("Bursa");
   city.insert("İstanbul");
   city.insert("Rize");
   city.insert("Antalya");
   city.insert("İzmir");
   city.insert("Hatay");
   city.insert("Ankara");
   city.insert("Zonguldak");

   iter = city.begin();           // display set
   while( iter != city.end() )
      cout << *iter++ << endl;

   string lower, upper;           // display entries in range
   cout << "\nEnter range (example A Azz): ";
   cin >> lower >> upper;
   iter = city.lower_bound(lower);
   while( iter != city.upper_bound(upper) )
      cout << *iter++ << endl;
   return 0;
}
