/******************************************************************
* ornek   : 3-3                                                	  *
* aciklama: girilen sayinin 3'e bölümünden kalani bulan program   *
* derleme : g++ -o program_ismi 3.cpp                 		      *
******************************************************************/

#include <iostream>

using namespace std;

int main()
{
	int sayi;
  
  	cout << "Bir sayi giriniz : ";
  	cin >> sayi;
  
  	if ((sayi % 3) == 0)
    	cout << "Sayi 3'un katidir\n";
  	else if ((sayi%3) == 2)
      	cout << "kalan 2'dir\n";
    else 
		cout << "kalan 1'dir\n";
  
  	return 0; 
}
