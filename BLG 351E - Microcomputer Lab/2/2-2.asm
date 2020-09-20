	ldaa	#$55
	cpx		#$4500
	ldaa	$10
	addb	$30
	staa	0,x
	cmpb	2,x
	ldaa	$4100
	cpx		$4200
	clra
	swi