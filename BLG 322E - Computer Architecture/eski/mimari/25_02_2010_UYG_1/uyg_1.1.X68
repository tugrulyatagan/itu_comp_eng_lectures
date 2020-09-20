*-----------------------------------------------------------------
* Program    : UYGULAMA _ I
* Written by : Araþ. Gör. Deniz DEMÝRAY
*	       Araþ. Gör. G. Selda KURUOÐLU
* Date       : 25.02.2010
* Description: Array Operations: reverse a given string
*------------------------------------------------------------------
	
; dizilerin tanimlanmasi:

	ORG     $2000		; initialized data 
N 	DC.B 	5
STRING	DC.B	'SELDA'		; between $2001 - $2005

	ORG     $2050		; uninitialized data 
REVERSE	DS.B	N	

	ORG	$1000
START:				; first instruction of program

	MOVE.B	N, D1   	; dizinin boyu D1 de
	
	LEA      STRING, A0  	; string adresi A0 da
	ADDA	 D1,A0		; son elemanin adresi + 1  A0 da (ön eksiltmeli erisim yapilacak)
	
	LEA      REVERSE, A1  	; reverse in baslangic adresi A1 de
	        
	SUBQ    #1, D1    	; dbf komutu döngüden -1'de ciktigi icin D1-1 den -1 e kadar tarama yapilacak
        
        
        
DEVAM   MOVE.B  -(A0),(A1)+	 ; dizi1 in elemanlari sira ile d0'a okunuyor
	
	; Test condition (F: false: kosul her zaman yanlýs!, Dn -1 oldugunda kendi cikiyor zaten),
	; decrement D1, and branch to DEVAM
	DBF     D1,DEVAM  	; dizi sonuna gelinmediyse DEVAM a geri git
        


	END	START		; last line of source






*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
