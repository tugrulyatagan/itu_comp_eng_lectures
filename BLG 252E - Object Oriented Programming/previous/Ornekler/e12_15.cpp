// e12_15.cpp
// http://www.buzluca.info/oop
//   map: cities and plate numbers **/
#include <iostream>
#include <map>
#include <string>         
using namespace std;

int main()
{                             // set of string objects
   map< string,int > city_num;
   city_num["Trabzon"]=61;     // insert city names and numbers
   city_num["Adana"]=01;
   city_num["Edirne"]=22;
   city_num["Bursa"]=16;
   city_num["Ýstanbul"]=34;
   city_num["Rize"]=53;
   city_num["Antalya"]=07;
   city_num["Ýzmir"]=35;
   city_num["Hatay"]=31;
   city_num["Ankara"]=06;
   city_num["Zonguldak"]=67;         
   
   string city_name;
   cout << "\nEnter a city: ";
   cin >> city_name;
   if (city_num.end()== city_num.find(city_name))
		cout << city_name << " is not in the database" << endl;
   else
        cout << "Number of " << city_name << ": " << city_num[city_name];
   return 0;
}
