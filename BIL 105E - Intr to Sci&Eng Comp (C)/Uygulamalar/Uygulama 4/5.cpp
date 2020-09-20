/************************************************************
* ornek   : 4-5												*
* aciklama: do-while ile 2'ser 2'ser sayan program			*
* derleme : g++ -o program_ismi 5.cpp						*
************************************************************/

#include <iostream>

using namespace std;
int main()
{
	int i = 30;
	
	do
	{
		cout << "i = " << i << endl;
		i += 2;
	} 
	while (i <= 20);

	return 0;
}



