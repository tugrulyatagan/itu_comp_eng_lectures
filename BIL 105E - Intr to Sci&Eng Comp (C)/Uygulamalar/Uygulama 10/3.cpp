/************************************************************************
*																		*
* ders 10 ornekleri									                    *
* cumleyi kelimelerine ayiran program									*
* derlemek icin g++ -o program_ismi 3.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;


int main()
{
	char cumle[]  = "Bugun hava guzel";
	char *kelime = cumle;
	int i = 1;
	
	cout<<"Cumle: "<<cumle<<endl;
    cout<<i++<<". kelime: ";

	while (*kelime != '\0'){
		if (*kelime == ' ') cout<<"\n"<<i++<<". kelime: "; 
		else cout<<*kelime; 
		kelime++;
	}
    cout<<endl;
	
	
	return 0;	
}
