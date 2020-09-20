/****************************************
* ornek   : 8-3							*
* aciklama: * ve & iliskisi				*
* derleme : g++ -o program_ismi 3.cpp	*
****************************************/
#include <iostream>
using namespace std;

int main()
{ 
	int sayi = 0, *ptr = &sayi;
	cout<<"sayi:"<<sayi<<",\t\tadresi:"<<&sayi<<endl;
	cout<<"*ptr:"<<*ptr<<",\t\tptr:"<<ptr<<"\t&ptr"<<&ptr<<endl;
	cout<<"*&ptr:"<<*&ptr<<",\t&*ptr:"<<&*ptr<<endl;
		
	return 0;
}
