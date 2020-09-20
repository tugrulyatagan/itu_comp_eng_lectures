#include <iostream>

using namespace std;

int main()
{

 char c1 = 'A', c2 = 'a';

 cout << "c1: " << c1 << " \t c2: " << c2 << " \n";
 cout << "c1 to int : " << static_cast <int>(c1) << " \n";
 cout << "c2 to int : " << static_cast <int>(c2) << " \n";

 c1 = 65;
 c2 = 98;

 cout << "char 65: " << c1 << " \n";
 cout << "char 98: " << c2 << " \n";

 return 0;

}

