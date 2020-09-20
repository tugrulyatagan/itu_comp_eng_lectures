#include <cstdio>
#include <iostream>

using namespace std;

#define yaz cout << "main fonksiyomumda i nin degeri: " << i;

void yazdir(int);
void bitir(void);

int main()
{
	int i=1; 
	
	yaz yazdir(i);
	yaz yazdir(i);
	yaz yazdir(i);

	bitir();

	return 0;
}

void yazdir(int i)
{
	static int a = 0;

	int b=0;
	a += i;
	b += i;

	cout << endl << "Yazdir fonksiyonunda  static a: " << a << "\t" << "b:" << b << endl;
}

void bitir(void)
{
	cout << "Program bitti..." << endl;
}
