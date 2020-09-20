/************************************************************************
*																		*
* ders 10 ornekleri 									                *
* char dizi ornegi 2													*
* derlemek icin g++ -o program_ismi 2.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;

int main()
{
	char kelime[15], *ptr;
	cin>>kelime;
	
	
	for (ptr = &kelime[0]; *ptr != '\0'; ptr++)
	{
		cout<<*ptr<<endl;     
	}	
	do
	    cout<<*ptr<<endl;
	
	while (ptr-- != kelime);

	return 0;
}
