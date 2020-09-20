#include <cstdio>
#include <iostream>

using namespace std;

int karenin_cevresi(int);
int karenin_alani(int);

int main()
{
	int a;

	cout << "Karenin kenarini giriniz: ";
	cin >> a;

	cout << "Karenin alani: " << karenin_alani(a) << endl;
	cout << "Karenin cevresi: " << karenin_cevresi(a) << endl;
	return 0;
}

int karenin_alani(int a)
{
	return a*a;
}

int karenin_cevresi(int a)
{
	return 4*a;
}

