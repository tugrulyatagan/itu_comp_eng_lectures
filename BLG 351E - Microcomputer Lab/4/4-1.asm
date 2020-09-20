	jmp	$4000
	.org $4000
	LDAA #$00
	STAA $8301 
	LDAA #$FF
	STAA $8300 
	LDAA #$04
	STAA $8301 
	LDAA #$00
	STAA $8300 
loop ldab	 #$00
	ldx #$4100
	stx	$4110
	clra
f	ldx $4110
	ldab 0,x
	stab	$8300
	inx
	inca
	stx	$4110
	JSR delay
	cmpa #$08
	blt f

	
	BRA loop
delay LDX #$0000
cnt INX
	CPX #$0003
	BEQ term
	BRA cnt
term RTS
;---------------------
	.org $4100
	.byte $1,$2,$4,$8,$10,$20,$40,$80