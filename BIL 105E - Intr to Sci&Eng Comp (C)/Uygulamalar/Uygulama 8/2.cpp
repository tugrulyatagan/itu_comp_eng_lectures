/****************************************
* ornek   : 8-2							*
* aciklama: pointera pointer ornegi		*
* derleme : g++ -o program_ismi 2.cpp	*
****************************************/

#include <iostream>
using namespace std;

int main()
{
	int n = 44;
		
	cout<<"n = "<<n<< "\t &n = "<<&n<<endl;

	int* pn = &n;

	cout<<"*pn = "<<*pn<<"\t pn ="<<pn<<"\t &pn ="<<&pn<<endl;
	
	int** ppn = &pn;
	
	cout<<"**ppn = "<<**ppn <<"\t *ppn = "<<*ppn<<"\t ppn = "<<ppn<<"\t &ppn = "<<&ppn<<endl;
	
	return 0;
}
