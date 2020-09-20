/************************************************************
* ornek   : 8-5												*
* aciklama: NULL ve void pointer ornegi						*
* 			NULL atanmis bir pointer hicbir yeri gostermez	*
* derleme : g++ -o program_ismi 5.cpp						*
************************************************************/

#include <iostream>
using namespace std;

int main()
{
	int *ptr;
	void *vPtr = NULL;	
	cout<<"ptr pointerinin gosterdigi:  "<<*ptr<<"\ticerigi: "<<ptr<<"\tadresi: "<<&ptr<<endl;

	vPtr = ptr;
	cout<<"vPtr pointerinin gosterdigi: "<<*(int *)vPtr<<"\ticerigi: "<<vPtr<<"\tadresi: "<<&vPtr<<endl;
	
	return 0;	
}
