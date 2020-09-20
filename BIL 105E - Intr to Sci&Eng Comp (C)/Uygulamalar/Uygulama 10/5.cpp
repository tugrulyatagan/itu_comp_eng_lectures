/************************************************************************
*																		*
* ders 10 ornekleri 								                	*
* kelimeyi buyuk harf yapan program										*
* derlemek icin g++ -o program_ismi 5.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;

int main()
{
	char kelime[100]= "BUgun hava gercekten cok guzel*";
	char  *ptr;
	int	fark = 'a' - 'A';
	
   	ptr = kelime;
	
		
	while(*ptr != '\0'){
		if ((*ptr >= 'a') && (*ptr <= 'z')) 
		    cout<<static_cast<char>(*ptr -fark );
			
		else 
		    cout<<*ptr;
			
		ptr++;
	}
	cout<<endl;

	return 0;
}
