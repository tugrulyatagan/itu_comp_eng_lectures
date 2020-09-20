#ifndef DUGUM_H_
#define DUGUM_H_

typedef int VERITIPI;

class Dugum
{
private:
      VERITIPI veri;
      Dugum* sonraki;
public:
	Dugum(VERITIPI);
	Dugum(VERITIPI,Dugum *);
	Dugum(const Dugum*&);
	Dugum* ekle(Dugum *);
	Dugum* ekle(VERITIPI);
	Dugum* cikart();
	VERITIPI getVeri();
	Dugum* sonra();
	~Dugum();
};

#endif /*DUGUM_H_*/
