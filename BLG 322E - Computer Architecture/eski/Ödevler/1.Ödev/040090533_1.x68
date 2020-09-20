*-----------------------------------------------------------
* Program    : HeapSort
* Written by : 
*	Name  : Abdullah AYDEÐER 
*	Number: 040090533
* Date       : 23.02.2012
* Description: Build-Max-Heap fonksiyonunun algoritmasýnýnýn MC68000 üzerinde gerçeklenmesi.
*-----------------------------------------------------------
	
	ORG $0400
size 	DC.W $000B

	ORG $0500
array 	DC.B $FF,$11,$13,$12,$14,$15,$16,$17,$18,$1A,$19	


;Functions
	ORG 	$0900
MxHp				*Altprogram baþlangýcý
	MOVEM.L	D2-D7/A0, -(A7)	*Altprogramda kullanýlan registerlarýn altprogramdan dönüþte içeriðinin deðiþmemesi için yýðýna atýldý.
	 
	MOVE.L	$20(A7),D7	*Yýðýndan parametre olarak gelen indis deðeri okundu.($20 = 32 birim aþaðýda)
	MOVE.W	D7, D5		*D5 = i(fonksiyona parametre olarak gelen deðiþken)'i göstermek için kullanýldý.
				
	ASL	#1, D7
	MOVE.W	D7, D6		*D6 = l(2*i) deðiþkeni için
	ADDQ	#1, D7		*D7 = r(2*i+1) deðiþkeni için
	
	MOVE.L	#array,A0	*A0 = Array'in baþlangýç adresi 	

	MOVE.B	(A0,D5.W),D3	*D3 = A[i] verisini tutmak için kullanýldý.
		
	CMP	size, D6	*If l(D6)>size -- 
	BGE	LEFT		*Ýleri dallanma olduðu için algoritmadaki koþulun tersi bir koþulla, yani l>=heap-size ise dallanma olacak LEFT etiketine
	CMP.B	(A0,D6.W),D3	*Else if A[i]>=A[l]
	BGE	LEFT		*Yine ileri dallanma olduðu için algoritmanýn tersi olarak A[i]>=A[l] ise dallanma olacak LEFT etiketine
	MOVE.W	D6, D4		*Else; largest(D4) <- l(D7) atamasý yapýlacak
	
	BRA	LEFTT		*Bu satýra inilmiþse koþulsuz olarak LEFTT etiketine dallanýlacak
	
LEFT	MOVE.W	D5, D4		*largest(D4) <- i(D5) atamasý yapýlýyor.

LEFTT	
	MOVE.B	(A0,D4.W),D3	*D3 = A[largest] yüklendi.
	
	CMP 	size, D7	*If heap-size>r		-- yukarýdakilere benzer þekilde koþullama ve dallanmalar...
	BGE 	RIGHT		*Branch RIGHT
	CMP.B	(A0, D7.W),D3	*Else if A[largest]>=A[r]
	BGE	RIGHT		*Branch RIGHT
	MOVE.W	D7, D4		*Else; largest(D4) <- r(D6) atamasý yapýldý
	
	
RIGHT	
	CMP	D4, D5		*If largest = i	Eðer birbirine eþitse doðrudan fonksiyon sonlanacak
	BEQ	BITIR		*Branch BITIR
	*Takas...		*Else, yani eþit deðilse takas iþlemini gerçekleþtirip, fonksiyonu largest deðeri için bir daha çaðýracak
	MOVE.B	(A0,D4.W),D3	*A[i]'yi D3 e atadýk
	MOVE.B	(A0,D5.W),D2	*A[largest]'ý D2 e atadýk
	MOVE.B	D2,(A0,D4.W)	*D2 A[i] ye yazýldý
	MOVE.B	D3,(A0,D5.W)	*D3 A[largest] a yazýldý
	
	MOVE.L	D4, -(A7)	*Fonksiyona largest parametresi yýðýn üzerinden hazýrlandý
	JSR	MxHp		*Fonksiyon kendini çaðýrdý.
	MOVE.L	(A7)+, D4	*Yýðýnla yollanan parametre yýðýndan geri çekildi.

BITIR
	MOVEM.L	(A7)+, D2-D7/A0	*Fonksiyonun baþýnda yýðýna atýlan register'lar, fonksiyon bitiminde yýðýndan geri çekildi.
	
	RTS			*Altprogramýn sonu...



	ORG	$1000
START:				; first instruction of program
	
	MOVE.W 	size, D0	*Size'ý rahatça kullanabilmek için D0 data register'ýna atýldý.(D0 <- size)
	ASR	#1, D0		*D0 = D0/2 yapýldý.
	
	MOVE.W	D0, D1		*D0'dan bir geride saymasý için bir sayac gerekliydi, bunun için de D1 register'ý kullanýldý.(D1 <- D0)
	
	SUBQ	#1, D1		*D1 D0'dan bir geride saymasý için D1 <- D1-1
	
GERI	
	MOVE.L	D0, -(SP)	*Ýndis deðeri yýðýn üzerinden gönderiliyor.
	JSR	MxHp		*Altprograma dallanýlýyor.
	SUBQ	#1, D0		*D0 elle bir azaltýlýyor.
	DBF	D1, GERI	*D1 '-1' den büyükse D1 <- D1-1 yapýlýp GERI etiketine dallanýlýyor.
	

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

* Variables and Strings



	END	START		; last line of source




*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
