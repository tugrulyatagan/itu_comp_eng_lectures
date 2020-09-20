/****************************************
* ornek   : 8-7							*
* aciklama: pointer / matris iliskisi	*
* derleme : g++ -o program_ismi 7.cpp	*
****************************************/

#include <iostream>
using namespace std;

void yaz(int *, int, int);

int main()
{
	int matris[3][3] = { {1, 2, 3},
					     {4, 5, 6},
					     {7, 8, 9}
					   },	 
		
		*ptr = (int *)matris;
	
	yaz(ptr, 3, 3);
	
	return 0;
}

void yaz(int *ptr, int satir, int sutun)
{
	int i;
	
	for (i = 0; i < satir*sutun; i++){
		cout<<*ptr++<<" "<<endl;		
	}
}
