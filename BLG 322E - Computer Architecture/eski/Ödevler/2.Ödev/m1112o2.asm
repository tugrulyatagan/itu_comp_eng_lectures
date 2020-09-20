SIFRE1		EQU $100
SIFRE2		EQU $200

METIN		EQU $300

ORG $100
DCCHR "JKLGHIMAEFDBCQRSTNOVWZUXPY"
ORG $200
DCCHR "HLMKIJDEFABCGRSYNOPQWTUXZV"
ORG $300
DCCHR "SAMPLETEXT"


ORG $600
SIFRELE:
	LDBU	(R26)R0,R16		
	NOP
	SUB	R16,$41,R16
	JMP BMI , EOF(R0) 
	NOP		
	
	LDBU	(R28)R16,R16
	STB	(R27)R0,R16
	
	ADD	R26,$01,R26		
;	ADD	R27,$01,R27		; bu satirdaki islem NOP yerine asagiya alinabilir.
	JMP BR , SIFRELE(R0) 
;	NOP
	ADD	R27,$01,R27	
		

EOF:	RET (R31)R0			; PC R15 ye kopyalanmisti, alt programda R15~R31
	NOP

                                             
ORG $700
START: 
	ADD 	R0 , METIN, R10		; Kaynak Adres -> R10	
	ADD 	R0 , $400, R11		; Hedef Adres -> R11	
	ADD	R0 , SIFRE1 , R12	; SIFRE  -> R12
	CALL	SIFRELE (R0) , R15	; degistir altprogram?na dallan?l?yor
					; PC -> R15 , degistir -> PC , CWP -1 -> CWP	
			NOP


	ADD 	R0 , $400, R10		; Kaynak Adres -> R10
	ADD 	R0 , $500, R11		; Hedef Adres -> R11	
	ADD	R0 , SIFRE2 , R12	; SIFRE  -> R12
	CALL	SIFRELE (R0) , R15	; degistir altprogram?na dallan?l?yor
					; PC -> R15 , degistir -> PC , CWP -1 -> CWP	


	NOP
	NOP				;program sonu