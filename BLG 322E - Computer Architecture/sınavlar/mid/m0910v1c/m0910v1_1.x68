
*-------------------------------------------------------------------------
* Program    : Ayir alt program ve test programý
* Written by : G. Selda KURUOÐLU -kuruoglug@itu.edu.tr
* Date       : 22.03.2010
* Description: Bilgisayar Mimarisi 2009-2010 bahar dönemi vize-1 soru:1
*-------------------------------------------------------------------------

*------------------------------------------------------------------------------------------
* SORU 1: (35 Puan)
*  MC68000 tabanl bir bilgisayar sisteminde 16 bitlik iaretsiz tamsaylardan oluan 
*  bir dizideki tek ve ift saylar belirleyip ayr dizilere yazan bir alt program 
*  (Ayir) yazlacaktr. Alt program giri parametresi olarak; kaynak dizinin balang 
*  adresini (Dizi, 32 bit), dizideki eleman saysn (n1, 16 bit), tek saylar ve ift 
*  saylar yerletirecei dizilerin balang adreslerini (Tek/Cift, 32 bit) alacaktr. 
*  Alt program ayrca tek ve ift saylarn adetini (nTek/nCift, 16 bit) geri dndrecektir. 
*  Tm parametreler yn zerinden aktarlacaktr. 

* a) Parametreleri uygun ekilde alt programa gnderip alt program aran ve geri dnen 
*    parametreleri (nTek/nCift) alp bellek gzlerine yazan ana program 68000 simgesel 
*    dilinde yaznz. Diziler ve deikenler iin istediiniz adresleri seebilirsiziniz.

* b) Tarif edilen altprogram (Ayir) 68000 mikroilemcisinin simgesel dilinde yaznz. 
*    Program yazarken mikroilemcinin komutlarn ve adresleme yeteneklerini program 
*    ksaltacak ekilde kullannz.
*------------------------------------------------------------------------------------------


* Program sonlandýðýnda oluþmasý gereken deðerler:

* $0600 adresinden itibaren dizinin tek elemanlar   : 1985 (07 C1), 3 (00 03), 33 (00 21), 45 (00 2D), 7 (00 07), 865 (03 61)
* $0650 adresinden itibaren dizinin cift elemanlar  : 198 (00 C6), 54 (00 36), 56 (00 38), 100 (00 64)
* $0700 adresinde dizide kaç adet tek eleman olduðu  : 6 (00 06)
* $0702 adresinde dizide kaç adet cift eleman olduðu : 4 (00 04)



; Tanmlamalar:

	ORG 	$0500
	
Dizi	DC.W	198, 1985, 54, 3, 33, 45, 7, 865, 56, 100
n1	DC.W	10	

	ORG 	$0600
	
Tek	DS.W	n1

	ORG     $0650
	
Cift	DS.W	n1

	ORG 	$0700
	
nTek	DS.W	1
nCift	DS.W	1
	
; Ayir ALTPROGRAMI:

	ORG	$1000
; Alt program çaðrýsý sonunda dönüþ adresi üzerinde dönüþ parametreleri bulunur:
; 16 bit: tek eleman says, 16 bit: çift eleman says

	
Ayir
	; Altprogramda kullanlan saklayýcýlar yýðýna atýlarak deðerleri korunur:
	MOVEM.L      A1-A3,-(SP)
	MOVEM.W      D0-D3,-(SP)
	
		
	MOVE.L    34(SP),A1	;  Dizi nin baslangic adresi A1 e alindi
    MOVE.W    32(SP),D0	;  Dizinin boyu D0 a alindi.
    MOVE.L    28(SP),A3      ;  Dizi deki tek elemanlarn yazlaca 'Tek' dizisinin baslangic adresi A3 e alindi
    MOVE.L    24(SP),A2      ;  Dizi deki ift elemanlarn yazlaca 'Cift' dizisinin baslangic adresi A2 ye alindi
	
	CLR.W D3			; tek eleman sayac 0 lanr
	CLR.W D2			; ift eleman sayac 0 lanr

DEVAM
	MOVE.W (A1)+,D1		; Sradaki Dizi elemann D1 e al
	
	BTST	#0, D1  
	BNE	TEKeleman
         	 
CIFTeleman
	ADDQ.W	#1, D2		; cift eleman saysn bir arttr
	MOVE.W	D1, (A2)+	; sradaki eleman ift elemanlar dizisine yaz
	BRA	ileri

TEKeleman
	ADDQ.W	#1, D3		; tek eleman saysn bir arttr
	MOVE.W	D1, (A3)+	; sradaki eleman tek elemanlar dizisine yaz
  
ileri   SUBQ.W	#1,D0
	BNE	DEVAM		; dizi sonuna gelinmediyse DEVAM a geri git
	
	; Tek eleman sayýsýný yýðýna yaz: (16 bit)- dn adresinden nceki (yýðýn azalarak ilerlediði için önceki) 16 bit
	MOVE.W	D3, 24(SP)
	
	; Çift eleman sayýssný yýðýna yaz: (16 bit)- tek eleman saysndan önceki 16 bit
	MOVE.W	D2, 26(SP)
	
	;Alt program baþýnda yýðýnda deðerleri saklanan saklayýclar geri okunur:
	MOVEM.L      (SP)+, A1-A3
	MOVEM.W      (SP)+, D0-D3

	RTS


; ANA PROGRAM

	ORG	$2000
	
START		MOVEA.W	    #$4000, SP		; Yigin $4000 adresinden baslatilmistir
           	PEA         Dizi                ; Dizi nin adesi yna atlyor
           	MOVE.W      n1,-(SP)		; Dizi nin boyu yna atlyor  
           	PEA	    Tek			; Dizideki Tek elemanlarn yazlaca bellek alannn adresi yna atlyor
           	PEA	    Cift		; Dizideki ift elemanlarn yazlaca bellek alannn adresi yna atlyor
           	JSR         Ayir          	; Ayir altprograminin cagirilmasi
		
		; Yýðýn üzerinden geri dönen deðerlerin ilgili bellek alanlarna yazýlmasý:
		MOVE.W	(SP)+, nTek		; ilk önce tek eleman saysn okur
		MOVE.W	(SP)+, nCift		; sonra çift eleman saysn okur
		
		MOVEA.W	    #$4000, SP		; Yigin gstergesini ilk haline getir, yýðýný boþalt
		
		              
		MOVE.B #9,D0		; 9 numarali islem yapilacak, programi bitir
		TRAP #15		; programi bitir
		END	START		; last line of source
