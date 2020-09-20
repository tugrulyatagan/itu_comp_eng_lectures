/************************************************************************
*																		*
* ders 10 ornekleri     								            	*
* string uzunlugu bulup kopyalayan program								*
* derlemek icin g++ -o program_ismi 7.cpp								*
*																		*
************************************************************************/

#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	char kelime[20], kopya[20];
	cin>>kelime;
	//gets(kelime);
	cout<<"Girilen kelime: "<<kelime<<endl;
	cout<<"Uzunlugu: "<<strlen(kelime)<<endl;
	strcpy(kopya, kelime);
	cout<<"kopyasi: "<<kopya<<endl; 
	
	return 0;
}
