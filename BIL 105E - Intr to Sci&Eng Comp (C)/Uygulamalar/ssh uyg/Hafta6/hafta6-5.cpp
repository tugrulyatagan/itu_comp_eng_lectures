#include <iostream>
#include <cstdio>

using namespace std;

void yaz(int a)
{
	cout << "Karenin cevresi = " << a << endl;
}

void hesapla(int a)
{
	yaz(4*a);
}

void devam(int b)
{
	hesapla(b);
}

int main()
{
	int c;
	cout << "Karenin kenarini giriniz: ";
	cin >> c;

	cout << "Karenin cevresi: " << devam(c) << endl;

	return 0;
}
