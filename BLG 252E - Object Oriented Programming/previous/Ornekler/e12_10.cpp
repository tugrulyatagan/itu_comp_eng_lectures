// e12_10.cpp
// http://www.buzluca.info/oop
// Sort example
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    string words[]= 
        {"november", "kilo", "mike", "lima", 
            "oscar", "quebec", "papa"};
    sort(words, words +7);
    for(int i =0 ; i<7; i++) cout << words[i] << endl;
	return 0;
}
