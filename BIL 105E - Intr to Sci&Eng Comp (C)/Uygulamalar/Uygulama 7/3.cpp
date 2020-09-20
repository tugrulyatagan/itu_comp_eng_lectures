/************************************************************************
* ornek   : 7-3															*
* aciklama: kare matrisin transpozunu alan program						*
* derleme : g++ -o program_ismi 3.cpp										*
************************************************************************/

#include <iostream>
using namespace std;

#define BOYUT 3


void yazdir(int[BOYUT][BOYUT]);

int main()
{
	int matris[BOYUT][BOYUT];
	int i, j;

	//matris okunuyor
	for (i = 0; i < BOYUT; i++)
		for (j = 0; j < BOYUT; j++)
			cin>>matris[i][j];
	
	yazdir(matris);
	
	int transpoz[BOYUT][BOYUT];
	for (i = 0; i < BOYUT; i++)
		for (j = 0; j < BOYUT; j++)
			transpoz[j][i] = matris[i][j];
	
	yazdir(transpoz);
	
	return 0;
}

void yazdir(int matris[BOYUT][BOYUT])
{
	int i, j;
	
	for (i = 0; i < BOYUT; i++){
		for (j = 0; j < BOYUT; j++)			
			cout<<matris[i][j]<<" ";		
		cout<<"\n";
	}
	
	cout<<"\n";
}
