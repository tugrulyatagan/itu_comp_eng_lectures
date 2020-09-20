/******************************************************************
* ornek   : 3-2                                                	  *
* aciklama: girilen sayinin tek mi cift mi oldugunu bulan program *
* derleme : g++ -o program_ismi 2.cpp                     	      *
******************************************************************/

#include <iostream>

using namespace std;

int main()
{	
	int sayi;
	
  	cout << "Bir sayi giriniz : ";
  	cin >> sayi;
	/*
  	if ((sayi % 2) == 0) 
  		cout << "Sayi cifttir\n";
    else
  		cout << "Sayi tektir\n";
	*/
	//(sayi % 2) == 0 ? cout << "Sayi cifttir\n" : cout << "Sayi tektir\n";
	cout << (!(sayi % 2) ? "Sayi cifttir\n" : "Sayi tektir\n");
  	return 0; 
}
