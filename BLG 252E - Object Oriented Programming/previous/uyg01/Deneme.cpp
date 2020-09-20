#include <iostream>
using namespace std;

#include "Liste.h"
#include "Tekil.h"

int main()
{
  Liste birListe;
  
  birListe.ekle(4);
  birListe.ekle(8);
  birListe.ekle(15);
  birListe.ekle(16);
  birListe.ekle(23);
  birListe.ekle(42);
  
  cout<<birListe.toString()<<endl;
  
  birListe.cikart(15);
  cout<<birListe.toString()<<endl;

  birListe.cikart(42);
  cout<<birListe.toString()<<endl;
  
  
  //Tekil birTek(3);
  //Tekil ikiTek(5); 
  
  cout<<Tekil::getInstance()->getVeri()<<endl;
  Tekil::getInstance()->setVeri(3);
  cout<<Tekil::getInstance()->getVeri();

  
}

