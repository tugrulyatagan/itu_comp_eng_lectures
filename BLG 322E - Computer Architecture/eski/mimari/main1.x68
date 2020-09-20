*
*-----------------------------------------------------------------
* Program    : Prime Number Testing
* Written By : Ar. Gör. G. Selda KURUOGLU (kuruoglug@itu.edu.tr)
*              Ar. Gör. Deniz DEMÝRAY     (demirayde@itu.edu.tr)
* Date       : 18.02.2010
* Description: Bilgisayar Mimarisi 2009-2010 ODEV - I:
*-----------------------------------------------------------------

;Veriler:

; Kýsým 1 icin:
 ORG $0500
testSayisi	DC.W	83		; asal sayi olup olmadigi test edilecek sayi
	   	
 ORG $0600 
sonuc     	DS.B 	1                ; sonuc: sayi asal ise 1, degil ise 0, baslangic degeri 2 
		
; ANA PROGRAM
	ORG	$1000
	
start		MOVEA.L	    #$4000,SP			; Yigin $4000 adresinden baslatilmistir
		
		; KISIM 1 : testSayisi asal mi?
		MOVE.B      #2, (sonuc)			; sonuc alanina 2 baslangic degeri veriliyor
		PEA 	    testSayisi                  ; test sayisinin adresi yigina atiliyor
		JSR         asalmi          		; asalmi altprograminin cagirilmasi
	
		MOVE.B 	    D7, sonuc			; alt programdan D7 uzerinden donen sonucun ilgili alana yazilmasi
   						
		MOVEA.L     #$4000,SP			; yiginin bosaltilmasi
		
		
;------------------------------------- asalmi ALTPROGRAMI: KODUNUZU BU ALANA YAZINIZ --------------------------------------


; -------------------------------------------------------------------------------------------------------------------------

		END	START					; last line of source








*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
