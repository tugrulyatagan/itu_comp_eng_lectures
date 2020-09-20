/************************************************************************
* ornek   : 7-5															*
* aciklama: ogrenci ders ortalamalarini hesaplayan program				*
* derleme : g++ -o program_ismi 5.cpp										*
************************************************************************/

#include <iostream>
using namespace std;

#define MAX_OGRENCI 20
#define MAX_DERS 10

int main()
{
	int ogrenci, ders, i, j;
	
	float tablo[MAX_OGRENCI][MAX_DERS] = {0.0},
		  ortalama[MAX_OGRENCI] = {0.0};
	
	
	cout<<"Sinifin ogrenci sayisini ve ders sayisini giriniz: ";	
	cin>> ogrenci >> ders ;
	
	if ( (ogrenci > MAX_OGRENCI) || (ogrenci <= 0) ){		
		cout<<"Ogrenci sayisi hatali girildi, lutfen kontrol ediniz...\n";
		return 1;
	}
	else if ( (ders > MAX_DERS) || (ders <= 0) ){
		cout<<"Ders sayisi hatali girildi, lutfen kontrol ediniz...\n";
		return 2;
	}
	else{ 
			//her ogrenci icin...
			for (i = 0; i < ogrenci; i++){
				cout<<"Ogrenci" << i <<" icin ders notlarini giriniz..\n";
				
				
				//not girisleri yapiliyor, ortalama hesaplaniyor
				for (j = 0; j < ders; j++){
					cout<< j <<".ders: ";
					cin>>tablo[i][j];
					ortalama[i] += tablo[i][j];
				} //for j
				
		 		ortalama[i] /= j;
		 	} //for i
		 	
			//her ogrenci icin...
			for (i = 0; i < ogrenci; i++)
				cout<<"Ogrenci" << i <<"ortalamasi: "<<ortalama[i];
			
		}	
	return 0;
}
