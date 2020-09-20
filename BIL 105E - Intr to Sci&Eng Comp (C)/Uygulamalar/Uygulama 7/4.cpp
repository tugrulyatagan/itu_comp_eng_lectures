/************************************************************************
* ornek   : 7-4															*
* aciklama: 2 matrisi carpan program									*
* derleme : g++ -o program_ismi 4.cpp										*
************************************************************************/

#include <iostream>
using namespace std;

#define BOYUT 2

typedef int matris_tip[BOYUT][BOYUT];

void yaz(matris_tip);

int main()
{
	matris_tip A, B, C = {0};
	int i, j, k;
	
	//matrisler okunuyor
	for (i = 0; i < BOYUT; i++)
		for (j = 0; j < BOYUT; j++)
			cin>>A[i][j];
	
	for (i = 0; i < BOYUT; i++)
		for (j = 0; j < BOYUT; j++)
			cin>>B[i][j];
		
	cout<<"MatrisA:\n";
	yaz(A);
	cout<<"MatrisB:\n";
	yaz(B);
	cout<<"MatrisC:\n";
	yaz(C);
	
	for (i = 0; i < BOYUT; i++)
		for (j = 0; j < BOYUT; j++)
			for (k = 0; k < BOYUT; k++)
				C[i][j] += A[i][k] * B[k][j];
	
	cout<<"NewMatrisC:\n";
	yaz(C);
	
	return 0;
}

void yaz(matris_tip matris)
{
	int i, j;
	
	for (i = 0; i < BOYUT; i++){
		for (j = 0; j < BOYUT; j++)			
			cout<<matris[i][j]<<" ";
		cout<<"\n";
	}
}
