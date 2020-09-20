/********************************************************
* ornek   : 5-9											*
* aciklama: sayiyi tersine ceviren fonksiyon			*
* derleme : g++ -o program_ismi 9.cpp					*
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;

int tersten(int sayi)
{
	int j, ters_sayi = 0;
	
	while (sayi > 0){
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
	cout<<"Sayiyi giriniz:";
	cin>>sayi;
	cout<<"Girilen sayinin tersi: \n"<<tersten(sayi);

	return 0;
}
