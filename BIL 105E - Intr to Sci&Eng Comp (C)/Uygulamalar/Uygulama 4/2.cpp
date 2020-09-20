/************************************************************
* ornek   : 4-2												*
* aciklama: uclu operator ile 2 sayinin karsilastirilmasi	*
* derleme : g++ -o program_ismi 2.cpp						*
************************************************************/

#include <iostream>

using namespace std; 
int main()
{
	int i, j;
	
	cout << "Farkli 2 sayi giriniz: ";
	cin >> i >> j;
	
	(i>j) ? cout << i << " > " << j << endl : cout << i << " < " << j << endl;

	return 0;	
}
