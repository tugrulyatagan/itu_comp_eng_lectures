#include <iostream>
#include <cstdio>

using namespace std;

int tersten(int sayi)
{
	int j, ters_sayi = 0;

	while (sayi > 0)
	{
		j = sayi % 10;
		sayi /= 10;
		ters_sayi *= 10;
		ters_sayi += j;
	}

	return ters_sayi;
}

int main()
{
	int sayi;
	cout << "Sayiyi giriniz: ";
	cin >> sayi;

	cout << "Sayinin tersi: " << tersten(sayi) << endl;

	return 0;
}
 
