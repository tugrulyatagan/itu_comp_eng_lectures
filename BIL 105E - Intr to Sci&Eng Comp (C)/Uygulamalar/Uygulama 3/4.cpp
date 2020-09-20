/***********************************************************
* ornek   : 3-4                                	    	   *
* aciklama: sayinin 5 ve 7ye bolunebilmesine bakan program *
* derleme : g++ -o program_ismi 4.cpp              		   *
***********************************************************/

#include <iostream>

using namespace std;

int main()
{
	int sayi;
  	
  	cout << "Sayi giriniz: ";
  	cin >> sayi;
 
 	if (( !(sayi % 5) && (sayi % 7)))
 		cout << "Sayi 5'e tam bolunur\n";
  	else if (( !(sayi % 7) && (sayi % 5)))
  		cout << "Sayi 7'ye tam bolunur\n";   		
  	else if (( !(sayi % 7) && !(sayi % 5)))
  		cout << "Sayi 5'e ve 7'ye tam bolunur\n"; 
  	else 
		cout << "2'sine de bolunmez\n";
  	
  	return 0; 
}
