/************************************************
* ornek   : 4-8									*
* aciklama: break-continue ornegi				*
* derleme : g++ -o program_ismi 8.cpp			*
************************************************/

#include <iostream>

#define DUR 5

using namespace std;
int main()
{
	int i, j, k;
	
	for (i = 0; i < DUR; i++)
	{
		
		for (j = 0; j < DUR; j++)
		{
			for (k = 0; k < DUR; k++)
			{
				if (k == 0) continue;
				cout << "k : " << k << endl;
			}	
			if (j == 0) break;
			    cout << "j : " << j << endl;
		}
		cout << "i : " << i << endl;
	}
	
	return 0;
}
