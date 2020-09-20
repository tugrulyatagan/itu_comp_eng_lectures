/********************************************************
* ornek   : 5-5											*
* aciklama: karenin cevresini ve alanini hesaplar		*
* derleme : g++ -o program_ismi 5.cpp					*
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;

int karenin_cevresi(int);
int karenin_alani(int);

int main()
{
	int a;
	
	cout << "Karenin kenarini girin: ";
	cin>> a;
		
	cout << "Karenin alani:" << karenin_alani(a)<< "\n";
	cout << "Karenin cevresi:"<< karenin_cevresi(a);
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
