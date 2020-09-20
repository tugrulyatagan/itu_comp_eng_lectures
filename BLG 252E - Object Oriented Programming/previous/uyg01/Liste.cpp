#include "Liste.h"

Liste::Liste()
{
  ilkDugum=NULL;
}

Liste::Liste(Dugum* d)
{
  ilkDugum=d;
}

Liste::Liste(VERITIPI veri)
{
  ilkDugum=new Dugum(veri);
}

Dugum* Liste::ara(VERITIPI veri)
{
    Dugum* gecici;
      
    for(gecici=ilkDugum;gecici && gecici->getVeri()!=veri   
                       ;gecici=gecici->sonra())
              ;

    return gecici;
}

Dugum* Liste::onceAra(VERITIPI veri)
{
  Dugum* gecici;
      
  for(gecici=ilkDugum;gecici->sonra() && gecici->sonra()->getVeri()!=veri
                            ;gecici=gecici->sonra())
              ;
  
  if(!gecici->sonra())
    gecici=NULL;
      
  return gecici;
}

Dugum* Liste::ekle(VERITIPI veri)
{
  Dugum* gecici;

  if(!ilkDugum)              
        gecici=bosaEkle(veri);
  else
  {
          for(gecici=ilkDugum;gecici->sonra();gecici=gecici->sonra())
                          ;
          gecici=sonaEkle(veri,gecici);
  }
  
  return gecici;  
}

Dugum* Liste::ekle(VERITIPI veri,Dugum* d)
{
  
  Dugum* gecici;

  if(!ilkDugum)              
          gecici=bosaEkle(veri);
  else if(d==ilkDugum)
          gecici=basaEkle(veri);
  else if(!d->sonra())
          gecici=sonaEkle(veri,d);
  else
          gecici=arayaEkle(veri,d);
  
  return gecici;  
}

Dugum* Liste::bosaEkle(VERITIPI veri)
{
  ilkDugum=new Dugum(veri);
  return ilkDugum;
}

Dugum* Liste::basaEkle(VERITIPI veri)
{
  ilkDugum=new Dugum(veri,ilkDugum);
  return ilkDugum;

}

Dugum* Liste::sonaEkle(VERITIPI veri,Dugum* d)
{
  d->ekle(veri);
  return d->sonra();
}

Dugum* Liste::arayaEkle(VERITIPI veri,Dugum* d)
{
  d->ekle(new Dugum(veri,d->sonra()));
  return d->sonra();
}

Dugum* Liste::cikart(VERITIPI veri)
{
   Dugum* gecici=ara(veri);
   Dugum* oncesi=onceAra(veri);

   if(!ilkDugum)              
           cout<<"Liste Bos!!\n";
   else if(gecici==ilkDugum)
           bastanCikart(gecici);
   else
           aradanCikart(oncesi,gecici);
   
   return gecici;     
}

void Liste::bastanCikart(Dugum* d)
{
  ilkDugum=d->cikart();
}

void Liste::aradanCikart(Dugum* once,Dugum* d)
{
  once->ekle(d->cikart());
}

string Liste::toString()
{       
  string sonuc="o";
  char* veri=new char(10);
  Dugum* gecici;

  for(gecici=ilkDugum;gecici;gecici=gecici->sonra())
  {
    sprintf(veri,"->%d",gecici->getVeri());
    sonuc=sonuc+veri;
  }
  
  sonuc=sonuc+"->/";
        
  return sonuc;
}

void Liste::bosalt()
{
  delete ilkDugum;
  ilkDugum=NULL;
}

Liste::~Liste()
{
  delete ilkDugum;
}
