/****************************************
* 										*
* aciklama: 3 boyutlu dizi ornegi		*
* derleme : g++ -o program_ismi 1.cpp		*
****************************************/

#include <iostream>
using namespace std;

int main()
{
	int dizi[2][3][4] = {0, 1},
		i = 0, j = 0, k = 0;
		
	for (i = 0; i < 2; i++){
		for (j = 0; j < 3; j++){
			for (k = 0; k < 4; k++){
				cout<<dizi[i][j][k]<<endl;
			}
		}
	}
	return 0;	
}
