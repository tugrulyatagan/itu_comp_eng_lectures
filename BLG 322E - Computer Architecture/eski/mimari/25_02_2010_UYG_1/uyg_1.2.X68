*-----------------------------------------------------------------
* Program    : UYGULAMA _ I
* Written by : Araþ. Gör. Deniz DEMÝRAY
*	       Araþ. Gör. G. Selda KURUOÐLU
* Date       : 25.02.2010
* Description: Array Operations: sum up DIZI1[i] & DIZI2[i], 
*				 store result in DIZI3[i]
*------------------------------------------------------------------
	
; dizilerin tanimlanmasi:

	ORG     $2000		; initialized data 

N 	DC.B 	10

DIZI1	DC.B	1,3,5,7,9,-5,7,8,46,78	;between $2001 - $200A
DIZI2	DC.B 	56,7,8,0,76,98,7,3,4,7  ;between $200B - $2014

	ORG	$2050           ; uninitialized data
	
DIZI3	DS.B	N


	ORG	$1000
START:				; first instruction of program

	LEA      DIZI1, A0  	; dizi1 in baslangic adresi A0 da
	LEA      DIZI2, A1  	; dizi2 in baslangic adresi A1 de
	LEA      DIZI3, A2  	; dizi3 in baslangic adresi A2 de
	
	
        
	MOVE.B	N, D1   	; dizinin boyu D1 de
	SUBQ    #1, D1    	; dbf komutu döngüden -1'de ciktigi icin D1-1 den -1 e kadar tarama yapilacak
        
        
        
DEVAM   MOVE.B  (A0)+, D0	 ; dizi1 in elemanlari sira ile d0'a okunuyor
	MOVE.B  (A1)+, D2	 ; dizi2 nin elemanlari sira ile d0'a okunuyor
	ADD.B 	D0,D2
	MOVE.B  D2,(A2)+	 ; toplamlarýný DIZI3 te ilgili yere yaz	

	; Test condition (F: false: kosul her zaman yanlýs!, Dn -1 oldugunda kendi cikiyor zaten),
	; decrement D1, and branch to DEVAM
	DBF     D1,DEVAM  	; dizi sonuna gelinmediyse DEVAM a geri git
        


	END	START		; last line of source






*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
