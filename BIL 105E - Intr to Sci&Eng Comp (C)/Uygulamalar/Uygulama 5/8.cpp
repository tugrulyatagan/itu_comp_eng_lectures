/************************************************************************
*																		
* Rekürsif olarak Fibonacci sayýlarýný hesaplar									
* derlemek icin: g++ -o program_ismi 8.cpp								
*																		
************************************************************************/

#include <iostream>

using namespace std;

int fib(int sayi)
{
    if(sayi==1 || sayi==0)
    return sayi;
    else
    return(fib(sayi-1) + fib(sayi-2));
}
int main()
{
    int sayi;
	cout<<"Kacinci Fibonacci Sayisi: ";   
	cin>> sayi;   
   cout<<sayi<<".Fibonacci Sayisi = "<<fib(sayi);

    return 0;
}
