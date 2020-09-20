n	.equ	6	;n ata
	ldab	#n	;b registeri n
	decb		;n--

	cmpb	#0	;n==0 ise
	blt		son	;bitir

	lds		#$ae	;stack pnt
	ldaa	#$1		;a=1
	psha			;stack'e at

	cmpb	#1		;n==1 ise
	blt		son		;bitir

d	tsx			;stack ptr x'e at
	adca	1,x	;a ile bir onceki elemani
	psha		;stack'e at
	decb		;n--
	tstb		;if not n==0
	bne		d	;dongu

son	staa	$0100	;sonucu kaydet
	.end			;bitir