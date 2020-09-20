n		.equ	#5
		ldx		#$0050
		lds     #$0080
		ldab #n
sub1	cmpb	#0
		ble		topla
		cmpb	#1 
		ble topla
sub3	decb
		pshb
		decb
		pshb
sub4	pulb
		sts $0050
		cpx 0081
		bge son
		jmp sub1
topla	INC $0090
	  	jmp sub4				
son 	.end