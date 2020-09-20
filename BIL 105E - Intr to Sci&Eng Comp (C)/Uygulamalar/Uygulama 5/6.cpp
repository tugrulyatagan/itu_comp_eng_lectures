/************************************************************************
*																		
* 10 elemanli int dizi yaratir, ilk 2 elemani 1							
* derlemek icin: g++ -o program_ismi 6.cpp								
*																		
************************************************************************/

#include <iostream>

using namespace std;
int main()
{
    int i, dizi[10] = {1,1};
     
	for (i = 0; i < 10; i++)
		cout<<"dizi ["<<i<<" ] = "<<dizi[i]<<"\n";
    return 0; 
}

