/********************************************************
* ornek   : 2-0                                         *
* aciklama: getchar  getc  putchar  putc  ornek program *
* derleme : g++ -o program_ismi 0.cpp                   *
********************************************************/
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	char c, d;
	
	cout << "karakteri girin: ";
	
	// klavyeden karakter girisi
	c = getc(stdin);	// c = cin.get();  alternatif
	d = getchar();		// d = cin.get();  alternatif
	
	/**
	* c = cin.get();
	* d = cin.get();
	* c ve d karakterlerini ilk giris yapilinca okur. Örnegin AB harfleri yanyana girilip
	* enter ile giris yapildiginda c = 'A', d = 'B' olur. Enter tusu da bir karakter olarak 
	* okunur. A + enter durumunda c = 'A', d = '\n' olur.
	* cin >> c >> d; alternatif olarak kullanilabilir.
	**/
	
	// ekrana karakter yazdirma
	putchar(c);
	putchar('\n');
	
	// ekrana karakter yazdirma
	putc(c, stdout);
	putc('\n',stdout);
	
	// ekrana karakter yazdirma
	cout << c;
	putchar(10);	// Satir atlama karakterinin Ascii tablosundaki karsiligi
	cout << d << "\n";
	
	return 0;
}
