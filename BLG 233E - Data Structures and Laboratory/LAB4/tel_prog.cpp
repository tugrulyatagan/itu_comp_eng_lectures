#include <iostream>
#include <stdlib.h>
#include <iomanip>
//#include <conio.h>
#include <ctype.h>
#include "diziislemleri.h"
#include <string>
using namespace std;
typedef Dizi Veriyapisi;
Veriyapisi defter;
Veriyapisi defter2;

void menu_yazdir();
bool islem_yap(char);
void kayit_ara();
void kayit_ekle();
void kayit_sil();
void kayit_guncelle();
void kayit_listele();

int main(){
	defter.olustur();
	bool bitir = false;
	char secim;
	while (!bitir) {
		menu_yazdir();
		cin >> secim;
		bitir = islem_yap(secim);
	}
	defter.temizle();
	return EXIT_SUCCESS;
}

void menu_yazdir(){
	cout << endl << endl;
	cout << "Phone Book Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Search Record" << endl;
	cout << "A: Add Record" << endl;
	cout << "U: Update Record" << endl;
	cout << "D: Delete Record" << endl;
	cout << "L: List Records" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter an option {S, A, U, D, L, E} : ";
}

bool islem_yap(char secim){
	bool sonlandir=false;
	switch (secim) {
	case 'S': case 's':
		kayit_ara();
		break;
	case 'A': case 'a':
		kayit_ekle();
		break;
	case 'U': case 'u':
		kayit_guncelle();
		break;
	case 'D': case 'd':
		kayit_sil();
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (Y/N):";
		cin >> secim;
		if(secim=='Y' || secim=='y'){
			sonlandir=true;
		}
		break;
	case 'L': case 'l':
		kayit_listele();
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {S, A, U, D, L, E} :" ;
		cin >> secim;
		sonlandir = islem_yap(secim);
		break;
	}
	return sonlandir;
}

void kayit_ara(){
	char ad[AD_UZUNLUK];
	cout << "Please enter the name of the person you want to search (press '*' for listing all):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	if(defter.ara(ad)==0)
		cout << "Record can not be found\n" << endl;
	getchar();
};

void kayit_ekle(){
	Tel_Kayit yenikayit;
	string geciciisim, gecicitelnumara;
	char *pgeciciisim, *pgecicitelnumara;
	cout << "Please enter the information of the person you want to save " << endl;
	cout << "Name : " ;
	cin.ignore(1000, '\n');
	getline(cin, geciciisim);
	cout << "Phone number :";
	cin >> setw(TELNO_UZUNLUK) >> gecicitelnumara;
	pgeciciisim = new char[geciciisim.length()+1];
	pgecicitelnumara = new char[gecicitelnumara.length()+1];
	strcpy(pgeciciisim,geciciisim.c_str());
	strcpy(pgecicitelnumara,gecicitelnumara.c_str());
	yenikayit.ad = pgeciciisim;
	yenikayit.telno = pgecicitelnumara;
	defter.ekle(&yenikayit);
	cout << "Record has been added" << endl;
	getchar();
};

void kayit_sil(){
	char ad[AD_UZUNLUK];
	int secim;
	cout << "Please enter the name of the person you want to delete (press '*' for listing all):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	int kisisayisi=defter.ara(ad);
	if(kisisayisi==0){
		cout << "Record can not be found" << endl;
	}
	else {
		if (kisisayisi==1){
			cout << "Record has been found." << endl;
			cout << "Please enter the index of the record if you want to delete this contact (Press -1 to exit without deletion): " ;
		}
		else
			cout << "Please enter the index of the record that you want to delete (Press -1 to exit without deletion): " ;
		cin >> secim;
		if(secim==-1) return;
		defter.sil(secim);
		cout << "Record has been deleted" <<endl;
	}
	getchar();
};

void kayit_guncelle(){
	char ad[AD_UZUNLUK];
	int secim;
	cout << "Please enter the name of the person you want to update (press '*' for listing all):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(ad,AD_UZUNLUK);
	int kisisayisi=defter.ara(ad);
	if(kisisayisi==0){
		cout << "Record can not be found" << endl;
	}
	else {
		if (kisisayisi==1){
			cout << "Record has been found." << endl;
			cout << "Please enter the index of the record if you want to update this contact (Press -1 to exit without updating) " ;
		}
		else
			cout << "Please enter the index of the record that you want to update (Press -1 to exit without updating): " ;
		cin >> secim;
		if(secim==-1) return;
		Tel_Kayit yenikayit;
		string geciciisim, gecicitelnumara;
		char *pgeciciisim, *pgecicitelnumara;
		cout << "Please enter the up-to-date information" << endl;
		cout << "Name : " ;
		cin.ignore(1000, '\n');
		getline(cin, geciciisim);
		cout << "Phone number :";
		cin >> setw(TELNO_UZUNLUK) >> gecicitelnumara;
		pgeciciisim = new char[geciciisim.length()+1];
		pgecicitelnumara = new char[gecicitelnumara.length()+1];
		strcpy(pgeciciisim,geciciisim.c_str());
		strcpy(pgecicitelnumara,gecicitelnumara.c_str());
		yenikayit.ad = pgeciciisim;
		yenikayit.telno = pgecicitelnumara;
		defter.guncelle(secim,&yenikayit);
		cout << "Record has been updated successfully" << endl;
	}
	getchar();
};

void kayit_listele(){
	defter.listele();
	getchar();
}
