#ifndef DIZIISLEMLERI_H
#define DIZIISLEMLERI_H
#include <stdio.h>
#include "kayit.h"
#define MAXKAYIT 100
struct Dizi{
	Tel_Kayit *head;
	int kayitsayisi;
	void olustur();
	void ekle(Tel_Kayit *);
	int ara(char *);
	void sil(int kayitno);
	void guncelle(int kayitno, Tel_Kayit *);
	void listele();
	void temizle();
};
#endif

                                                                                                                                                                                                                                                                                                                                                                            
