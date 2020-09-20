/********************************************
* BLG 233E DATA STRUCTURES AND LABORATORY	*
* CRN: 11146								*
* HOMEWORK 1								*
* MATRIX	CALCULATOR						*
* TUGRUL YATAGAN							*
* 040100117									*
********************************************/
// list.h
// LinkedList yapisinin tanimlamasi
// buradaki fonkisyonlarin matrix_operations da tanimlanmistir
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h" // Node yapisi dahil edilir

struct LinkedList{
	Node *head; // LinkedList matrisinin ilk elemanini gosterir
	int row, col; // LinkedList matrisinin satir sutun sayilari
	void create(); // LinkedList olusturur
	void generaterand(); // istenilen buyuklukte rastgele elemanli matris bagli liste olusturur
	void readfile(); // matris dosyasini okur ve matris bagli listeye atar
	int scanright(int); // bagli listedeki elemanlari matris duzeninde saga dogru tarar ve degerini doner
	int scandown(int); // bagli listedeki elemanlari matris duzeninde asagi dogru tarar ve degerini doner
	void print(); // bagli listeyi matris seklinde ekrana yazdirir
	void transpose(); // matrisin transpozunu alir ve ekrana yazdirir
	bool symmetry(); // matrisin simetrikligini kontrol eder (simetrik matris ise 1 doner)
	bool zero(); // matrisin sifir matris olup olmadigin kontrol eder (sifir matris ise 1 doner)
	int determinant(); // matrisinin determinantini alir
	void clear(); // bellekten alinan bagli listeleri geri iade eder
};

int randomnum(); // rastgele sayi uretir (generaterand icinde kullanilir)
void multiply(); // carpma fonkiyonu matrisleri referansla degil disaridan aldigi icin linked list structina dahil degil

#endif 
