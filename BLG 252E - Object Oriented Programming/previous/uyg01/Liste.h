#ifndef LISTE_H_
#define LISTE_H_
#include "Dugum.h"
#include <iostream>
using namespace std;
#include <string>

class Liste
{
private:
        Dugum* ilkDugum;
        Dugum* bosaEkle(VERITIPI);
        Dugum* basaEkle(VERITIPI);
        Dugum* sonaEkle(VERITIPI,Dugum*);
        Dugum* arayaEkle(VERITIPI,Dugum*);
        void bastanCikart(Dugum*);
        void aradanCikart(Dugum*,Dugum*);
        
public:
	Liste();
	Liste(Dugum*);
	Liste(VERITIPI);
	Dugum* ara(VERITIPI);
	Dugum* onceAra(VERITIPI);
	Dugum* ekle(VERITIPI);
	Dugum* ekle(VERITIPI,Dugum*);
	Dugum* cikart(VERITIPI);
	string toString();
	void bosalt();
	~Liste();
};

#endif /*LISTE_H_*/
