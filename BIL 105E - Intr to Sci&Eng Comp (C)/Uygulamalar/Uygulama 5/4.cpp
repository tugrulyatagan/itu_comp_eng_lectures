/************************************************************************
*																		
* 10 elemanli int dizi yaratir, elemanlari sifirlar, ekrana yazar		
* derlemek icin: g++ -o program_ismi 4.cpp								
*																		
************************************************************************/
#include <iostream>

using namespace std;

int main()
{
	int i, dizi[10] ;
    
    for (i = 0; i < 10; i++) dizi[i] = 0; 
    for (i = 0; i < 10; i++)
    	cout<<"dizi ["<<i<<"] = "<<dizi[i]<<"\n";
    
    return 0; 
}
