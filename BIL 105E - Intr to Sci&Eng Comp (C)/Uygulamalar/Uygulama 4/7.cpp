/****************************************************************
* ornek   : 4-7													*
* aciklama: while ile girilen cumleyi buyuk harf yapan program	*
* derleme : g++ -o program_ismi 7.cpp							*
****************************************************************/

#include <iostream>

using namespace std;
int main()
{
	char c;
	
	do
	{
		cin >> c;	
		if (c != '\n') 
		{
		    if (!((c >= '0') && (c <= '9')))
		    {
			    c = c - 'a';
			    c = c + 'A';
			    cout << "c: " << c << endl;
		    }
		}
	} 
	while (c != '0');

	return 0;
}
