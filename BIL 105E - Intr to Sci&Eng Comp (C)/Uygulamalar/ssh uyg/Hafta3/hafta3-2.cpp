#include <iostream>
#include <cstdio>

using namespace std;

int main()
{

 char c, d;
 cout << "karakteri giriniz: ";
 c = getc(stdin);
 d = getchar();

 putchar(c);
 putchar('\n');

 putc(c, stdout);
 putc('\n',stdout);

 cout << c;
 putchar(10);

 cout << d << "\n";

 return 0;

}
