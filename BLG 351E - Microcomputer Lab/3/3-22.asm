	lds		#$5f00
	ldaa	#$23
	psha
	jsr		sub
	pula
	swi
sub	tsx
	ldab	2,x
	rts