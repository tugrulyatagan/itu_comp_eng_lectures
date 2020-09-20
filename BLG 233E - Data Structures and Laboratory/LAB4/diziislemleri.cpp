#include <iostream>
#include <stdlib.h>
//#include <cstdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "diziislemleri.h"
using namespace std;

void Dizi::olustur(){
	head = NULL;
	kayitsayisi = 0;
}

int Dizi::ara(char *aranacak){
	Tel_Kayit *traverse;
	int sayac=0;
	int bulunan = 0;
	traverse = head;
	bool tumu=false;
	bool bitir=true;
	if(strcmp(aranacak,"*")==0)
		tumu=true;
	while (traverse && bitir){
		sayac++;
		if (tumu){
			cout << sayac << "." << traverse->ad << " " <<traverse->telno <<endl;
			bulunan++;
		}
		else if (strnicmp(traverse->ad, aranacak, strlen(aranacak)) == 0){
			bulunan++;
			cout << sayac << "." << traverse->ad << " " <<traverse->telno <<endl;
		}
		if (strnicmp(traverse->ad, aranacak, strlen(aranacak)) > 0) //exit loop when searches are found
			bitir=NULL;
		traverse = traverse->next;
	}
	return bulunan;
}

void Dizi::ekle(Tel_Kayit *ykptr){
	Tel_Kayit *traverse, *tail; 
	Tel_Kayit *newnode = new Tel_Kayit;;
	traverse = head;
	*newnode = *ykptr;
	newnode->next = NULL;
	if (head == NULL){//first node being added
		head = newnode;
		kayitsayisi++;
		return;
	}
	if (strcmp(newnode->ad, head->ad) < 0){ //Insert to head of list 
		newnode->next = head; 
		head = newnode; kayitsayisi++; 
		return; 
	} 
	while (traverse && (strcmp(newnode->ad, traverse->ad) > 0)){ 
		tail = traverse; 
		traverse = traverse->next; 
	} if (traverse){ // Insert into a position 
		newnode->next = traverse; 
		tail->next = newnode; 
	} 
	else // Insert to end 
		tail->next = newnode; 
	kayitsayisi++; 
}

void Dizi::sil(int kayitno){
	Tel_Kayit *traverse, *tail;
	int sayac = 1;
	traverse = head;
	if (kayitno <= 0){
		cout << "Invalid record order number.\n";
		return;
	}
	if (kayitno == 1){
		head = head->next;
		delete traverse;
		kayitsayisi--;
		return;
	}
	while ((traverse != NULL) && (sayac < kayitno)){
		tail = traverse;
		traverse = traverse->next;
		sayac++;
	}
	if (sayac < kayitno){// given order num too large
		cout << "Could not find record to delete.\n";
	}
	else{ // record found
		tail->next = traverse->next;
		delete traverse;
		kayitsayisi--;
	}
}

void Dizi::guncelle(int kayitno, Tel_Kayit *ykptr){
	Tel_Kayit *traverse, *tail;
	int sayac = 1;
	traverse = head;
	if (kayitno <= 0){
		cout << "Invalid number for record to be updated.\n";
		return;
	}
	if (kayitno == 1){
		head = head->next;
		delete traverse;
		kayitsayisi--;
	}
	else{
		while ((traverse != NULL) && (sayac < kayitno)){
			tail = traverse;
			traverse = traverse->next;
			sayac++;
		}
		if (sayac < kayitno){// given order num too large
			cout << "Invalid number for record to be updated.\n";
		}
		else{ // record found
			tail->next = traverse->next;
			delete traverse;
			kayitsayisi--;
		}
	}
	Tel_Kayit *newnode;
	traverse = head;
	newnode = new Tel_Kayit;
	*newnode = *ykptr;
	newnode->next = NULL;
	if (head == NULL){//first node being added
		head = newnode;
		kayitsayisi++;
		return;
	}
	if (strcmp(newnode->ad, head->ad) < 0){ //Insert to head of list 
		newnode->next = head; 
		head = newnode; kayitsayisi++; 
		return; 
	} 
	while (traverse && (strcmp(newnode->ad, traverse->ad) > 0)){ 
		tail = traverse; 
		traverse = traverse->next; 
	} if (traverse){ // Insert into a position 
		newnode->next = traverse; 
		tail->next = newnode; 
	} 
	else // Insert to end 
		tail->next = newnode; 
	kayitsayisi++;
}

void Dizi::listele(){
	Tel_Kayit *traverse;
	traverse = head;
	for(int i=0;i<kayitsayisi;i++){
		cout << i+1 << "." << traverse->ad << " " <<traverse->telno <<endl;
		traverse = traverse->next;
	}
}

void Dizi::temizle(){
	Tel_Kayit *p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
	kayitsayisi = 0;
}
