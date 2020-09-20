*-----------------------------------------------------------
* Program    : Recursive Max-Heapify Function 
* Written by : Gökhan SEÇ?NT?
* Date       : 13.02.2012
* Description:
*-----------------------------------------------------------

* Variables 
	ORG	$0400
size	DC.W	$000B
	ORG	$0500
array	DC.B	$FF,$11,$13,$12,$14,$15,$16,$17,$18,$1A,$19,$20
	
	
	


* Functions
	ORG	$0600

HEAP:	MOVEM.W D0-D4/A0-A2,-(SP)
	MOVE.W	$14(SP),D3		;retrive function parameter
	
	MOVE.W	D3,D2
	ASL.W	#1,D2
	MOVE.W	D2,D1			;left at D1
	ADDQ	#1,D2			;right at D2

	LEA	array,A0
	LEA	array,A1
		
	CMP.W	(size),D1
	BGE	eof
	ADD.W	D1,A0
	ADD.W	D3,A1
	CMPM.B	(A1)+,(A0)+		;cmp  A[indice], A[left]
	BLE	next1
	MOVE.W	D1,D3
next1:	

	
	LEA	array,A0
	LEA	array,A1	
	
	CMP.W	(size),D2
	BGE	next2
	ADD.W	D2,A0
	ADD.W	D3,A1
	CMPM.B	(A1)+,(A0)+		;cmp  A[indice], A[right]
	BLE	next2
	MOVE.W	D2,D3
next2:	
	
	
	
	CMP.W	$14(SP),D3		;largest <> indice
	BEQ	eof
	;SWAP 
	LEA	array,A0
	LEA	array,A1
	
	MOVE.W	$14(SP),D1
	ADD.W	D1,A0
	MOVE.B	(A0),D4
	
	ADD.W	D3,A1
	MOVE.B	(A1),(A0)
	MOVE.B	D4,(A1)
	
	
	;Function call
	MOVE.W	D3,-(SP)	;send parameter
	JSR	HEAP		;function call
	ADDQ	#2,SP		;remove parameter from stack



eof:	MOVEM.W (SP)+,D0-D4/A0-A2
	RTS	

	
	
	
* Main	
	ORG	$1000
	
START:	MOVEA.L	    #$4000,SP			; SP <- $4000
	MOVE.B	#1,D1
		
	MOVE.W	(size),D1
	ASR.W	#1,D1
loop:		
		
	MOVE.W	D1,-(SP)	;send parameter
	JSR	HEAP		;function call
	ADDQ	#2,SP		;remove parameter from stack

	SUBQ	#1,D1
	CMP.W	#1,D1
	BGE	loop

	MOVE.B	#9,D0
	TRAP	#15		; halt simulator

	END	START		; last line of source



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
