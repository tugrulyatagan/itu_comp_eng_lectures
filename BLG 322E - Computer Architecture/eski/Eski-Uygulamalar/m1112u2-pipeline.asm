; pipeline'nın etkin kullanımı için yapılan degisiklikler *** ile işaretlenmiştir.


SIZE	EQU $0A	
sARRAY	EQU $100
tARRAY	EQU $200



ORG $050
	DCINT -1

ORG $100
	DCINT 11
	DCINT -12
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
NEXT:
	STL(R27)R0,R10		; Burada ayni geli�tirme islemi yap�lmas� bir sat�r kod yaz�lmas� gerekiyor.
	RET (R31)R0			; PC R15 ye kopyalanmisti, alt programda R15~R31
	NOP

ORG $400
NEGATIVE:	
	
	ADD	R0, $50, R16
	LDL	(R16)R0,R17	
	NOP
	XOR	R26,R17,R26	
	NOP
	
	RET (R31)R0	  		; PC R15 ye kopyalanmisti, alt programda R15~R31
	ADD	R10,1,R10		; ***(1) R26'yi bir �st pencerede arttir.
                                      
ORG $500
START: 


	ADD	R0, SIZE, R17
	ADD	R0, R0, R14		; COUNTER R16 yerine diger pencereden erisilebilen r14 kullanildi

loop:				; *** (2) Simulator hatasından kaynaklanan NOP'lar kaldırıldı.
	ADD 	R0, sARRAY, R10	; s_ARRAY -> R10
	ADD 	R0 , tARRAY, R11	; t_ARRAY -> R11
	ADD	R10, R14, R10
	ADD	R11, R14, R11
		
	CALL	COPY (R0) , R15		; degistir altprogram?na dallan?l?yor
					; PC -> R15 , degistir -> PC , CWP -1 -> CWP	
	
				; ***(3)
	ADD	R30, 4, R30		; bu penceredeki R14 (counter) degerini diger pencerede de�istir
	SUB	R17, 1, R17
	JMP