#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;

void Dizi::yaz(){
	fseek(teldefteri, 0, SEEK_SET);
	for(int i = 0; i < kayitsayisi; i++){
		fwrite(k+i, sizeof(Tel_Kayit), 1, teldefteri);
		fwrite("\n", 1, 1, teldefteri);
	}
}

void Dizi::ekle(Tel_Kayit *ykptr){
	Tel_Kayit *ptr;
	if(kayitsayisi == 0){
		ptr = &k[kayitsayisi];
		strcpy(ptr->ad,ykptr->ad);
		strcpy(ptr->telno,ykptr->telno);
		kayitsayisi++;
	}
	else{
		int i = 0;
		while(strcmp(ykptr->ad, k[i].ad) > 0 && i < kayitsayisi)
			i++;
		int temp = kayitsayisi;
		for(int j = 0; j <= kayitsayisi - i - 1; j++){
			strcpy(k[temp].ad, k[temp-1].ad);
			strcpy(k[temp].telno, k[temp-1].telno);
			temp--;
		}
		ptr = &k[i];
		strcpy(ptr->ad, ykptr->ad);
		strcpy(ptr->telno,ykptr->telno);
		kayitsayisi++;
	}
}
void Dizi::olustur(){
	kayitsayisi = 0;
	dosyaadi="teldefteri.txt";
	teldefteri = fopen( dosyaadi, "r+" );
	if(!teldefteri){
		if(!(teldefteri = fopen( dosyaadi, "w+" ))){
			cerr << "File can not be opened" << endl;
			exit(1);
		}
	}
	fseek(teldefteri, 0, SEEK_SET);
	while(!feof(teldefteri)){
		fread((k+kayitsayisi), sizeof(Tel_Kayit)+1, 1, teldefteri);
		kayitsayisi++;
	}
	kayitsayisi--;
}

int Dizi::ara(char aranacak[]){
	int sayac=0;
	bool tumu=false;
	int bulunan,flag=0;
	if(strcmp(aranacak,"*")==0)
		tumu=true;
	for(int i=0;i<kayitsayisi;i++){
		if(strcmp(k[i].ad,aranacak)==0)
		{
			cout<<i+1<<". "<<k[i].ad<<endl;
			bulunan=i;
			flag=1;
		}
	}
	return flag;
}
void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr){
	strcpy(k[kayitno-1].ad,ykptr->ad);
	strcpy(k[kayitno-1].telno,ykptr->telno);
}
void Dizi::sil(int kayitno){
	Tel_Kayit temp;
	int yer = kayitno - 1;
	for(int j=0; j<kayitsayisi - yer;j++){
		strcpy(k[yer].ad, k[yer+1].ad);
		strcpy(k[yer].telno, k[yer+1].telno);
		yer++;
	}
	strcpy(k[kayitsayisi].ad, "");
	strcpy(k[kayitsayisi].telno, "");
	kayitsayisi--;
}
void Dizi::listele(){
	for(int i=0;i<kayitsayisi;i++)
		cout<<i+1<<". "<<k[i].ad<<" \t"<<k[i].telno<<endl;
}
