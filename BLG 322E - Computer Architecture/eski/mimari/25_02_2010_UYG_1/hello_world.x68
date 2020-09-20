*-----------------------------------------------------------
* Program    : Hello World
* Written by : Deniz Demiray & Selda Kuruoglu
* Description: Ekrana Hello World 12345678 yazar
*-----------------------------------------------------------

* Asagidaki satir, programin bellegin neresinde bulunacagini belirtir
* dolar isareti ($) sayinin 16lik tabanda olduunu belirtir (hexadecimal)
	ORG	$1000		; program $1000 adresinde

* START   -> etiket
* MOVE	  -> opcode
* #14, D0 -> operand
START:	MOVE #14,D0		; 14 sayisini D0 saklayicisina
				; basta # olmasaydi, 14 adresinin icerigi D0 saklayicisina olurdu
				
	LEA HELLO,A1		; HELLO nun adresi A1 adres saklayicisina 
				; artik A1, HELLO adresindeki stringe isaret ediyor
				
	TRAP	#15		; TRAP #15 i/o isleminde kullanilir
				; yapilacak islem D0 saklayicisinda belirtilir
				; burada 14 islemi, A1 in isaret ettigi stringi yazdir demek
				
	MOVE.L #12345678,D1	; 12345678 sayisi D1 saklayicisina
	MOVE #3,D0		; 3 numarali islem yapilacak, D1 deki isaretli sayiyi yazdirmak
	TRAP #15		; D1 deki sayiyi yaz
	
	MOVE.B #9,D0		; 9 numarali islem yapilacak, programi bitir
	TRAP #15		; programi bitir

* DC.B byte uzerinden islem yap
* string ' ' arasina yazilir
* $D -> carriage return
* $A -> new line
* 0  -> null terminator
HELLO DC.B 'Hello World',$D,$A,0 ;$D,$A yi kaldirirsak alt satira gecmez
					
	END	START		; END -> programin sonu
				; START tan baslayarak programi calistir


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
