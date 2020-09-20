/************************************************************
* ornek   : 4-4												*
* aciklama: while ile 2'ser 2'ser sayan program				*
* derleme : g++ -o program_ismi 4.cpp						*
************************************************************/

#include <iostream>

using namespace std;
int main()
{
	int i = 0;
	
	while (i <= 20)
	{
		cout << "i = " << i << endl;
		i += 2;
	}

	return 0;
}
