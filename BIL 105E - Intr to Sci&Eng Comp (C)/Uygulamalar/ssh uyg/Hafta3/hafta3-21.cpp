#include <iostream>
#include <cstdio>

using namespace std;

int main()
{

 char c, d;
 cout << "karakteri giriniz: ";
 cin >> c >> d;

 putchar(c);
 putchar('\n');

 putc(c, stdout);
 putc('\n',stdout);

 cout << c;
 putchar(10);

 cout << d << "\n";

 return 0;

}

