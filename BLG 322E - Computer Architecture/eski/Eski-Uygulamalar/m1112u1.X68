

* Variables and Strings
	ORG  	$0100
array1:	DC.B	$01,$01,$01,$01,$01,$FF	

	ORG  	$0200
array2:	DC.B	$02,$02,$02,$02,$02,$FF

	ORG  	$0300
array3:	DC.B	$03,$03,$03,$03,$03,$FF



;Functions
	ORG  	$0900
SUM:	MOVEM.W D0-D2/A0-A1,-(SP)
	MOVE.W	$0E(SP),A0 	;parameter
	
	CLR	D1
loop:	MOVE.B	(A0)+,D0
	BMI	eof
	ADD.B	D0,D1
	BRA	loop

eof:	MOVE.W	D1,$0e(SP)
	MOVEM.W (SP)+,D0-D2/A0-A1
	RTS

	ORG	$1000
START:	MOVEA.L		#$4000,SP			; SP <- $4000
	
	LEA	 	array1,A1
	LEA		array2,A2
	LEA		array3,A3
	CLR		D0
	

	
	MOVE.W		A1,-(SP)
	JSR		SUM
	ADD.W		(SP)+,D0	
	
	
	MOVE.W		A2,-(SP)
	JSR		SUM
	ADD.W		(SP)+,D0	
	
	
	MOVE.W		A3,-(SP)
	JSR		SUM
	ADD.W		(SP)+,D0	
	
	
	

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
