	clra
	clrb
	ldx 	#$4400
l	adda	0,x
	inx
	incb
	cmpb	#$0A
	blt		l
	staa	$4440
	swi
