/********************************************************
* ornek   : 5-7											*
* aciklama: fonksiyonlarla karenin cevresini hesaplar	*
* derleme : g++ -o program_ismi 7.cpp					*
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;
 
 void yaz(int a)
 {
 	//cout<<"Karenin cevresi = %d\n",a);	
	cout<<"Karenin cevresi = "<< a;	
}
 
 void hesapla(int a)
 {
 	yaz(4*a);	
 }
 
 void devam(int a)
 {
 	hesapla(a);
 }
 
 int main()
 {
 	int a;
 	
 	cout<<"Karenin kenarini girin:";
 	cin>> a;
 	devam(a);
 	
	return 0;	
 }
