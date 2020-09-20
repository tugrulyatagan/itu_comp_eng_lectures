	ORG $0
DIZI:
	DCINT	3
	DCINT	66
	DCINT	-2
	DCINT	75
	DCINT	125

;DS Sözde komutu kullaným örneði (10 sekizli yer ayýrýr)
DIZI1	DS 10

;Bu altprogram R31 ve R30 saklayýcýlarýnda aldýðý tamsayýlarý çarparak
;sonucu 64 bitlik bir deðer olarak R29(Yüksek anlamlý) ve R28 saklayýcýlarýnda 
;döndürür. Dönüþ adresinin R27 saklayýcýsýnda verilmesi gerekir
;Russian gibi daha verimli bir algoritma kullanýlabilirdi ama benzetim açýsýndan 
;daha uzun iþlem gerektiren ardýþýl toplama tercih edildi

CARPIM:	ADD R0,R0,R28	;R28 ve R29 u sýfýrla
	ADD R30,R0,R25	;Çarpan sayýyý R25 e al (R30 u deðiþtirmiyoruz)
	JMPR BMI,NEGATIF
	ADD R0,0,R24	;Negatif çarpan için bayrak
	ADD R0,R0,R29
GERI:	JMPR BEQ,BITTI	
DEVAM:	ADD R31,R28,R28
	ADDC R0,R29,R29
	JMPR BR,GERI
	NOP
	SUB R25,1,R25
BITTI:	ADD R0,R24,R24
	JMPR BEQ,PZTF
	SUB R28,R31,R28
	SUBC R29,R0,R29		;Sonraki NOP veri baðýmlýlýðýný çözmek için
	NOP			
	SUBR R28,0,R28
	SUBCR R29,0,R29 
PZTF:	RET (R27)0
	NOP
	NOP

NEGATIF: JMPR BR,DEVAM
	SUB R0,R25,R25
	ADD R0,1,R24	

;Bu altprogram R31 saklayýcýsýnda baþlangýç adresini ve R30 saklayýcýsýnda eleman sayýsýný aldýðý 
;tamsayý dizisinin en büyük elemanýný bularak R29 saklayýcýsýnda geri döndürür. Dönüþ adresi 
;R28 saklayýcýsýnan okunur. R30 saklayýcýsýnda gelen parametrenin 0 dan büyük olduðu varsayýlmýþtýr

MAX:	ADD R0,4,R23		;Her elemanýmýz 4 sekizli boyutunda
	ADD R0,1,R25		;Sayaç olarak kullanýlacak saklayýcýya 1 yazdýk 
	LDL (R31)0,R29		;En büyük eleman dizinin ilk elemaný
DONGU1:	LDL (R31)R23,R24	;Dizinin sýradaki elemaný R24 de
	SUB R30,R25,R0		;Sonucu bir yere yazmýyoruz, R0 donanýmsal olarak sýfýrda
	JMPR BEQ,SON
	ADD R23,4,R23		;Bir sonraki eleman adresi için
	SUB R29,R24,R0		;Karþýlaþtýrma için... sonucu bir yere yazmýyoruz
	JMPR BGE,DONGU1
	ADD R25,1,R25		;Sayacý bir artýr, dallanma gerçekleþse de gerçekleþmese de yapýlacak
	NOP
	JMP BR,DONGU1(R0)
	ADD R0,R24,R29		;Daha büyük olan elemaný R29 a al
	NOP
SON:	RET (R28)0
	NOP
	NOP
	

;Bu altprogram R31 saklayýcýsýnda baþlangýç adresini ve R30 saklayýcýsýnda eleman sayýsýný aldýðý 
;tamsayý dizisinin en küçük elemanýný bularak R29 saklayýcýsýnda geri döndürür. Dönüþ adresi 
;R28 saklayýcýsýnan okunur. R30 saklayýcýsýnda gelen parametrenin 0 dan büyük olduðu varsayýlmýþtýr

MIN:	ADD R0,4,R23		;Her elemanýmýz 4 sekizli boyutunda
	ADD R0,1,R25		;Sayaç olarak kullanýlacak saklayýcýya 1 yazdýk 
	LDL (R31)0,R29		;En küçük eleman dizinin ilk elemaný
DONGU2:	LDL (R31)R23,R24	;Dizinin sýradaki elemaný R24 de
	SUB R30,R25,R0		;Sonucu bir yere yazmýyoruz, R0 donanýmsal olarak sýfýrda
	JMPR BEQ,SON1
	ADD R23,4,R23		;Bir sonraki eleman adresi için
	SUB R29,R24,R0		;Karþýlaþtýrma için... sonucu bir yere yazmýyoruz
	JMPR BLE,DONGU2
	ADD R25,1,R25		;Sayacý bir artýr, dallanma gerçekleþse de gerçekleþmese de yapýlacak
	NOP
	JMP BR,DONGU2(R0)
	ADD R0,R24,R29		;Daha küçük olan elemaný R29 a al
	NOP
SON1:	RET (R28)0
	NOP
	NOP

;Ana program, bir tamsayý(32 bitlik) dizisinin en büyük ve en küçük elemanlarýný bularak çarpýmlarýný (64 bit)
;hesaplayýp sonucu bellekte $200(yüksek anlamlý) ve $201 adresli gözlere yazar
;(Örnek, Prof.Dr. Eþref Adalý ve Yrd.Doç.Dr.Þule Gündüz Öðüdücü 2005 yýlý Mikroiþlemci Sistemleri yýliçi sýnav sorusudur)

START:	ADD R0,START,R13	;Sadece saklayýcý dosyasý deðiþimini görmek için yapýlan bir yükleme
	SLL R13,3,R30		;Veri baðýmlýlýðý oluþturmak için eklendi
	ADD R0,$66,R8		;Sadece saklayýcý dosyasý deðiþimini görmek için yapýlan bir yükleme
	ADD R0,-20,R18		;Sadece saklayýcý dosyasý deðiþimini görmek için yapýlan bir yükleme	
	SUB& R0,R0,R19		;Etkilenmeyen durum kütüðü bayraklarýný göstermek için eklendi

	CALLR MAX,R12		;Dönüþ adresi çaðrýlan altprogramýn R28 saklayýcýsýnda (bu pencerede R12)
	ADD R0,DIZI,R31		;Dikkat !!! Okunan ve yazýlan saklayýcýlar farklý pencerelerde
	ADD R0,5,R30
	ADD R0,R13,R5		;MAX altprogramýndan R28=R13 saklayýcýsýnda dönen deðer yerel saklayýcýya alýndý
	CALL MIN(R0),R12	;Altprogram parametreleri zaten ilgili saklayýcýlarda yüklü NOP		
	NOP
	NOP
	ADD R0,R13,R14		;Altprogramýn R31 saklayýcýsýna MAX,  R30 saklayýcýsýna MIN altprogramlarýndan gelen deðerler yazýlýyor
	CALL CARPIM(R0),R11
	ADD R0,R5,R31		;Dikkat !!! Okunan ve yazýlan saklayýcýlar farklý pencerelerde
	NOP
	STL (R0)$200,R13
	STL (R0)$204,R12
	

	
	
