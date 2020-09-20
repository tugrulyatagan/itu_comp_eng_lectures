/************************************************************
* ornek   : 4-9												*
* aciklama: while ile girilen sayiyi tersten yazan program	*
* derleme : g++ -o program_ismi 9.cpp						*
************************************************************/

#include <iostream>

using namespace std;
int main()
{
	int sayi;
	
	cout << "Sayiyi giriniz: ";
	cin >> sayi;
	
    int i = sayi, j;
    
    while (i > 0)
    {
    	j = i % 10;
    	cout << j;
		i /= 10;
    }
    
    cout << endl;

	return 0;
}
