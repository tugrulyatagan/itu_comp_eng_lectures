
; Bir sayý dizindeki sayýlarý baþka bir adrese taþýyan ve
; bu iþlem sýrasýnda negatif sayýlarý ikiye tümleyerek mutlak  
; deðerlerini hesaplayan program örneði


;	Ýki altprogram
;		1- COPY : parametre olarak kaynak adresi ve hedef adresi gönderiliyor.
;					(gerekiyorsa NEGATIVE fonk. ile tümleyenini hesaplayarak) 
;					Kaynak adresdeki 4 sekizliði hedefe taþýyor. 
;		2- NEGATIVE: Parametre olarak gönderilen sayýnýn ikiye tümleyenini hesaplýyor.
;	Ana program
;		Dizideki eleman sayýsý kadar tekrar eden bir döngü içerisinde COPY fonksiyonunu çaðýrýyor.
;
;

SIZE	EQU $0A	
sARRAY	EQU $100
tARRAY	EQU $200


; Tümleme işleminde kullanılan FFFFFFFF değişkeni
ORG $050
	DCINT -1		

ORG $100
	DCINT -12
	DCINT 10
	DCINT -10
	DCINT 10
	DCINT 10
	DCINT 10
	DCINT -10
	DCINT -10
	DCINT 10
	DCINT 10

ORG $300
COPY:	
	LDL	(R26)R0,R10
	NOP
	ADD	R0,R10,R10
	JMP	BPL,NEXT(R0)
	NOP	
	CALL	NEGATIVE(R0),R15
	NOP
NEXT:	STL	(R27)R0,R10	
EOFC:	RET (R31)R0			; PC R15 ye kopyalanmisti, alt programda R15~R31
	NOP


ORG $400
NEGATIVE:	
	
	ADD	R0, $50, R16
	LDL	(R16)R0,R17	
	NOP
	XOR	R26,R17,R26	
	NOP
	ADD	R26,1,R26
EOFN:	RET (R31)R0	  		; PC R15 ye kopyalanmisti, alt programda R15~R31
	NOP	
                                      
ORG $500
START: 


	ADD	R0, SIZE, R17
	ADD	R0, R0, R16		; COUNTER
loop:		
	ADD 	R0, sARRAY, R10		; s_ARRAY -> R10
	NOP
	ADD	R10, R16, R10

	ADD 	R0 , tARRAY, R11	; t_ARRAY -> R11	
	NOP
	ADD	R11, R16, R11
	

	CALL	COPY (R0) , R15		; degistir altprogram?na dallan?l?yor
					; PC -> R15 , degistir -> PC , CWP -1 -> CWP	
	NOP

	ADD	R16, 4, R16		; index for integer (4 byte )
	SUB	R17,