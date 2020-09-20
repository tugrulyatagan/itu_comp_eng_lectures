/************************************************************************
*																		
* 10 elemanli fibonacci dizisi yapar									
* derlemek icin: g++ -o program_ismi 7.cpp								
*																		
************************************************************************/

#include <iostream>
using namespace std;
int main()
{
	int i, dizi[10] = {1,1};
    
    for (i = 2; i < 10; i++)
    	dizi[i] = dizi[i-1] + dizi[i-2];   
    
    for (i = 0; i < 10; i++)
   		cout<<"dizi ["<<i<<" ] = "<<dizi[i]<<"\n";
    return 0; 
}

