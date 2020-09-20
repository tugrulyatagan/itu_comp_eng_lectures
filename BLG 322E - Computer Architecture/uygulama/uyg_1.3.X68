
*--------------------------------------------------------------------------------------------------
* Program    : Array Operations: copy nth, n/2 th, n/4th ... 1 st element of an array to the end of the array

* Written By : Ar. Gör. G. Selda UYANIK 	(seldauyanik@itu.edu.tr)
*              Ar. Gör. Gokhan SECINTI     	(secinti@itu.edu.tr)
* Date       : 17.02.2011
* Description: Bilgisayar Mimarisi 2010-2011 	UYGULAMA - I:
*---------------------------------------------------------------------------------------------------	
; dizilerin tanimlanmasi:

	ORG     $2000		; ilk degeri verilmis olan veriler 

N 	DC.W 	16
DIZI1	DC.B 	1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16  	;$2002 - $2011 adresleri arasinda

; program calistrildiginda olusmasi gereken dizi:
; 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, 16,8,4,2,1  		;$2002 - $2016 adresleri arasinda


	ORG	$2050           ; ilk degeri belirsiz olan veriler	
DIZI2	DS.B	5		; N in fonksiyonu olarak hesaplanabilir


	ORG	$1000
START:				
	LEA      DIZI1, A0  	; dizi1 in baslangic adresi A0 da
	MOVEA.L	 A0, A1
	MOVE.W	 N, D1   	; dizinin boyu D1 de, sýralý eriþimde index olarak kullanýlacak
	ADDA	 D1,A1 		; dizi1 in son elemanindan sonraki bellek gozunun adresi A1 de
	

KOPYALA:	MOVE.B -1(A0,D1.L),(A1)+
		LSR.L	#1,D1
		BNE	KOPYALA
		
        
	MOVE.B #9,D0		; 9 numarali islem yapilacak, programi bitir
	TRAP #15		; isletim sistemine donus

	END	START		













*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
