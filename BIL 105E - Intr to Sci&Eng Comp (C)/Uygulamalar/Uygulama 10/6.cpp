/************************************************************************
*																		*
* ders 10 ornekleri     								             	*
* string sayinin karesini alan program									*
* derlemek icin g++ -o program_ismi 6.cpp								*
*																		*
************************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;


int main()
{
	char sayi[5];
	int Sayi;
	cout<<"Sayiyi giriniz: ";
	cin>>sayi;

	cout<<"Girilen string: "<<sayi<<endl;
	
	Sayi = atoi (sayi) ;//Convert string to integer
	cout<<"Sayi hali:  "<<Sayi<<endl;
	cout<<"Karesi:     "<<Sayi*Sayi<<endl;

	return 0;
}
