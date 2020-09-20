#include <iostream>
using namespace std;

#include "Dugum.h"

Dugum::Dugum(VERITIPI veri)
{
  this->veri=veri;
  this->sonraki=NULL;  
}

Dugum::Dugum(VERITIPI veri,Dugum *sonraki)
{
  this->veri=veri;
  this->sonraki=sonraki;  
}

Dugum::Dugum(const Dugum*& kopya)
{
  this->veri=kopya->veri;
  this->sonraki=kopya->sonraki;  
}

Dugum* Dugum::ekle(Dugum *sonraki)
{
  this->sonraki=sonraki;
  return this->sonraki;
}

Dugum* Dugum::ekle(VERITIPI veri)
{
  this->sonraki=new Dugum(veri);
  return this->sonraki;
}

Dugum* Dugum::cikart()
{
  Dugum* gecici=this->sonraki;
  this->sonraki=NULL;
  return gecici;
}

VERITIPI Dugum::getVeri()
{
  return veri;
}

Dugum* Dugum::sonra()
{
  return sonraki;
}

Dugum::~Dugum()
{
    delete this->sonraki;
}
