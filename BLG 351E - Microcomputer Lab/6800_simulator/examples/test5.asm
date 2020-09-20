ten 	.equ	10	
sum10   clra ;A	=	0	
		ldab #ten ;B	=	10	
loop1   aba ;A	=	A	+	B		
		decb ;B--	
		tstb ;test	(B==0)	
		bne	loop1 ;repeat	if	B!=0	
		staa	sum ;sum	=	A
;---------	variables	----------
sum 	.rmb	1 ;same	as	.byte		
		.end		