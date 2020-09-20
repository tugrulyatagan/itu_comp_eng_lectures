/********************************************************
* ornek   : 5-8											*
* aciklama: fonksiyonlarda statik ve dinamik degiskenler*
* derleme : g++ -o program_ismi 8.cpp					*
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;
#define yaz cout<< "main fonksiyonunda i nin degeri: "<< i;

void yazdir(int);
void bitir();

int main()
{
	int i = 1;
	
	yaz yazdir(i);
	yaz yazdir(i);
	yaz yazdir(i);
	
	bitir();
	
	return 0;
}

void yazdir(int i)
{
	static int a = 0; //will only be executed once
					//the keyword static prevents re-initialization of the variable
	int b = 0;	
	a += i; //a=a+i;
	b += i;
		
	cout<<"\nYazdir fonksiyonunda static a:"<<a<<"\t"<< "b:"<<b<<"\n" ;
}

void bitir()
{
	printf("Program bitti...\n");
}
