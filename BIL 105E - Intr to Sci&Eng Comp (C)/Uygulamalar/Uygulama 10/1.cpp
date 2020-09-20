/************************************************************************
*																		*
* ders 10 ornekleri								                        *
* char dizi ornegi 1, 													*
* derlemek icin g++ -o program_ismi 1.cpp								*
*																		*
************************************************************************/

#include <iostream>
using namespace std;
int main()
{
	char kelime[] = {'d', 'e', 'n', 'e', 'm', 'e','\0'}; 
	//'\0' is the null character used to terminate strings 
	cout<<kelime<<endl;
    return 0;
}
