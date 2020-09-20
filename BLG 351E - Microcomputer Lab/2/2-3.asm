	.org 0
	clra
	clrb
	ldx #$4200
	stx $4400
	ldx #$4300
	stx $4500
	ldx #$4100
	stx $4600
label ldaa 0,x
	inx
	stx $4600
	rora
	bcs tek
	rola
	ldx $4400
	staa 0,x
	inc $4401
	incb
	ldx $4600
	cmpb #$0A
	blt label
tek	rola
	ldx $4500
	staa 0,x
	inc $4501
	incb
	ldx $4600
	cmpb #$0A
	blt label
	


	.org $4100
	.byte 1,2,3,4,5,6,7,8,9,10



