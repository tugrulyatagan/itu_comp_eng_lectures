#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;


void Dizi::ekle(Tel_Kayit *ykptr){
	if(kayitsayisi == boyut){
		Tel_Kayit* yeni;
		yeni = new Tel_Kayit[2*boyut];
		for(int i = 0; i < boyut; i++)
		{
			yeni[i].ad = new char[strlen(k[i].ad)];
			strcpy(yeni[i].ad,k[i].ad);
			yeni[i].telno = new char[strlen(k[i].telno)];
			strcpy(yeni[i].telno,k[i].telno);
		}
		boyut *= 2;
		delete[] k;
		k = new Tel_Kayit[boyut];
		for(int i = 0; i < kayitsayisi; i++)
		{
			k[i].ad = new char[strlen(yeni[i].ad)];
			strcpy(k[i].ad,yeni[i].ad);
			k[i].telno = new char[strlen(yeni[i].telno)];
			strcpy(k[i].telno,yeni[i].telno);
			delete[] yeni[i].ad;
			delete[] yeni[i].telno;
		}
		delete[] yeni;
	}
	Tel_Kayit *ptr;
	if(kayitsayisi == 0){
		ptr = &k[kayitsayisi];
		ptr->ad = new char[strlen(ykptr->ad)];
		ptr->telno = new char[strlen(ykptr->telno)];
		strcpy(ptr->ad,ykptr->ad);
		strcpy(ptr->telno,ykptr->telno);
		kayitsayisi++;
	}
	else{
		int i = 0;
		while(i < kayitsayisi && strcmp(ykptr->ad, k[i].ad) > 0)
			i++;
		int temp = kayitsayisi;
		for(int j = 0; j <= kayitsayisi - i - 1; j++){
			k[temp].ad = new char[strlen(k[temp-1].ad)];
			k[temp].telno = new char[strlen(k[temp-1].telno)];
			strcpy(k[temp].ad, k[temp-1].ad);
			strcpy(k[temp].telno, k[temp-1].telno);
			temp--;
		}
		ptr = &k[i];
		ptr->ad = new char[strlen(ykptr->ad)];
		ptr->telno = new char[strlen(ykptr->telno)];
		strcpy(ptr->ad, ykptr->ad);
		strcpy(ptr->telno,ykptr->telno);
		kayitsayisi++;
	}
}
void Dizi::olustur(){
	kayitsayisi = 0;
	k = new Tel_Kayit[ILKBOYUT];
	boyut = ILKBOYUT;
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
	delete k[kayitno-1].ad;
	delete k[kayitno-1].telno;
	k[kayitno-1].ad = new char[strlen(ykptr->ad)];
	k[kayitno-1].telno = new char[strlen(ykptr->telno)];
	strcpy(k[kayitno-1].ad,ykptr->ad);
	strcpy(k[kayitno-1].telno,ykptr->telno);
}

void Dizi::sil(int kayitno){
	for(int i = kayitno-1; i < kayitsayisi-1; i++)
	{
		delete k[i].ad;
		delete k[i].telno;
		k[i].ad = new char[strlen(k[i+1].ad)];
		k[i].telno = new char[strlen(k[i+1].telno)];
		strcpy(k[i].ad, k[i+1].ad);
		strcpy(k[i].telno, k[i+1].telno);
	}
	delete k[kayitno].ad;
	delete k[kayitno].telno;
	kayitsayisi--;
}

void Dizi::listele(){
	for(int i=0;i<kayitsayisi;i++)
		cout<<i+1<<". "<<k[i].ad<<" \t"<<k[i].telno<<endl;
}

void Dizi::iade(){
	delete[] k;
}