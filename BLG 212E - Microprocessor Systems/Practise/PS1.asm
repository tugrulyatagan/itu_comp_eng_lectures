        .ORG $0000
        LDAA #4
        STAA $000A
        LDAA #8
        STAA $000F
        LDAA #0
        STAA $000B
        .ORG $0010
START   LDX #$0100
        CLRB
BACK	LDAA ,x
        CMPA $000F
	    BHI FORWARD
        PSHA  
        INC $000B
FORWARD INCB
        CMPB $000A
	    BEQ WRITE
	    INX
	    BRA BACK
WRITE   CLRB 
        LDX #$0200
BACK2   PULA
        INCB
        STAA ,x
        INX
        CMPB $000B
        BNE BACK2
        .ORG $0100
ARY1    .byte 3,9,2,4
        .end

