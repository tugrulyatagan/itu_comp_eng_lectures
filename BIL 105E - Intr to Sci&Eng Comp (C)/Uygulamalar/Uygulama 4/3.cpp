/************************************************************
* ornek   : 4-3												*
* aciklama: while ile 1 den j ye kadar sayan program		*
* derleme : g++ -o program_ismi 3.cpp						*
************************************************************/

#include <iostream>

using namespace std;
int main()
{
	int i = 0, j;
	
	cout << "Pozitif bir tamsayi girin: ";
	cin >> j;
	
	while (i < j) cout << "i nin degeri: " << ++i << endl; //i+1
	
	return 0;	
}
