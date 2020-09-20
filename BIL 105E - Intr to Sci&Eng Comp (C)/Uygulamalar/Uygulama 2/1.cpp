/*************************************************
 * ornek   : 2-1                                 *
 * aciklama: karakterler ve sayisal karsiliklari *
 * derleme : g++ -o program_ismi 1.cpp           *
 ************************************************/

#include <iostream>

using namespace std;

int main()
{
	char c1 = 'A', c2 = 'a';
	
	cout << "c1: " << c1 << " \t c2ders: " << c2 << " \n"; 			//printf("c1: %c \t c2: %c\n",c1,c2);
	cout << "c1 to int : " << static_cast<int>(c1) << " \n";	//printf("c1 to int: %i \n", c1);
	cout << "c2 to int : " << static_cast<int>(c2) << " \n";	//printf("c2 to int: %i \n", c2);
																//printf in <cstdio>
	c1 = 65;
	c2 = 97;
	
	cout << "char 65: " << c1 << " \n";		//printf("char 65: %c \n", c1);
	cout << "char 97: " << c2 << " \n";		//printf("char 98: %c \n", c2);

    return 0;
}
