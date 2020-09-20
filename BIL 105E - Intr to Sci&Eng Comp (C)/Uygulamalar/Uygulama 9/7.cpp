/************************************************************************
*																		*
* ders 9 ornekleri 										                *
* new ile dinamik dizi yaratma									        *
* derlemek icin g++ -o program_ismi 7.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;

int main()
{
	int *dizi, i, uzunluk;
	
	cout<<"Dizinin uzunlugunu girin:"<<endl;
    cin>>uzunluk;
    dizi=new int[uzunluk];	
	
	for (i = 0; i < uzunluk; i++)
        cout<<&dizi[i]<<endl;

	cout<<"Girilen dizi yazdiriliyor...\n";

	for (i = 0; i < uzunluk; i++)
	   cout<<dizi[i]<<endl;	
     	
	cout<<"\n";
	cout<<"Bellek bosaltiliyor...\n";
	delete(dizi);
	
	return 0;	
}
