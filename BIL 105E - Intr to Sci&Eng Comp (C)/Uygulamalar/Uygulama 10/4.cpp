/************************************************************************
*																		*
* ders 10 ornekleri - Deniz Demiray										*
* cumleyi kelimelerine ayirip tersten yazan program						*
* derlemek icin g++ -o program_ismi 4.cpp								*
*																		*
************************************************************************/

#include <iostream>

using namespace std;

int main()
{
	char bas[] = "Bugun hava gercekten cok guzel";
	char *son, *yaz, *tmp, c;
	
	son = bas;
	cout<<"Cumle: "<<son<<endl;
	
	
	while (*son != '\0') son++;
	
	
	do{
		yaz = son;		
		while((*yaz != ' ') && (yaz != bas)) yaz--;
		tmp = yaz;		
		if (yaz == bas) break;
		while(yaz++ != son) cout<<*yaz; 
		cout<<" ";
		son = --tmp;
		
	}while (1);
	
	yaz--;

	while(yaz++ != son) cout<<*yaz; 
	cout<<"\n";
	return 0;	
}
