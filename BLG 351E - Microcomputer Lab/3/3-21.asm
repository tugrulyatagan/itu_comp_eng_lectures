		lds		#$5f00
		jsr		sub1
		swi
sub1	jsr		sub2
		rts
sub2	rts