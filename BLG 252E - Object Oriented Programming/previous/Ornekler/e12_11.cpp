// e12_11.cpp
// http://www.buzluca.info/oop
// The sort algorithm uses the after function

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
bool after( const string &left, const string &right)
{
	return left > right;
}

int main()
{
    string words[]= 
        {"november", "kilo", "mike", "lima", 
            "oscar", "quebec", "papa"};
    sort(words, words +7, after);
    for(int i =0 ; i<7; i++) cout << words[i] << endl;
	return 0;
}
