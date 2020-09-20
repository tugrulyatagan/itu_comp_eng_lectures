
*-------------------------------------------------------------------------------
* Program    : Array Operations: reverse a given string 
* Written By : Ar. Gör. G. Selda UYANIK 	(seldauyanik@itu.edu.tr)
*              Ar. Gör. Gokhan SECINTI     	(secinti@itu.edu.tr)
* Date       : 17.02.2011
* Description: Bilgisayar Mimarisi 2010-2011 	UYGULAMA - I:
*-------------------------------------------------------------------------------
	
; dizilerin tanimlanmasi:

	ORG     $2000		; ilk degeri verilmis olan veriler 
N 	DC.W 	5
STRING	DC.B	'SELDA'		; $2002 - $2006 adresleri arasinda

	ORG     $2050		; ilk degeri belirsiz olan veriler 
REVERSE	DS.B	N	

	ORG	$1000
START:				

	MOVE.W	 N, D1   	; dizinin boyu D1 de
	
	LEA      STRING, A0  	; string adresi A0 da
	ADDA	 D1,A0		; son elemanin adresi + 1  A0 da (ön eksiltmeli erisim yapilacak)
	
	LEA      REVERSE, A1  	; reverse in baslangic adresi A1 de
	        
	SUBQ    #1, D1    	; dbf komutu döngüden -1'de ciktigi icin D1-1 den -1 e kadar tarama yapilacak
        
        
        
DEVAM   MOVE.B  -(A0),(A1)+	 ; dizi1 in elemanlari sira ile d0'a okunuyor
	
	; Test condition (F: false: kosul her zaman yanlýs!, Dn -1 oldugunda kendi cikiyor zaten),
	; decrement D1, and branch to DEVAM
	DBF     D1,DEVAM  	; dizi sonuna gelinmediyse DEVAM a geri git
        
	
	MOVE.B #9,D0		; 9 numarali islem yapilacak, programi bitir
	TRAP #15		; isletim sistemine donus

	END	START		













*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
