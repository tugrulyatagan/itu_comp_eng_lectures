/********************************************
* BLG 233E DATA STRUCTURES AND LABORATORY	*
* CRN: 11146								*
* HOMEWORK 1								*
* MATRIX	CALCULATOR						*
* TUGRUL YATAGAN							*
* 040100117									*
********************************************/
// node.h
// Node yapisinin tanimlamasi
struct Node{
	int value; // matrisin elaminin degeri
	Node *right; // elemanin sagindaki elemani gosteren isaretci
	Node *down; // elemanin altindaki elemani gosteren isaretci
};
