       .ORG $000A
VAL    .byte $12,$00,$04,$13,$00
       .ORG $0010
BASE   .equ $000A 
NEW    .equ $000D
LENGTH .equ $000C 
ODD    .equ $0006 
EVEN   .equ $0008 
TEMP   .rmb 1     
START   LDX BASE 
        STX ODD
	    STX EVEN  
        CLRB
        LDX ODD
BACK    LDAA ,x
        STAA TEMP
	    ANDA #$01
        BNE ODDBRA
        INX
        BRA BACK
BACK2   LDAA ,x
        STAA TEMP
	    ANDA #$01
        BEQ EVENBRA
        INX
        BRA BACK2
ODDBRA  LDAA TEMP
        PSHA
        INX
        STX ODD
		INCB
        CMPB LENGTH
        BEQ WRITE
        LDX EVEN
        BRA BACK2
EVENBRA LDAA TEMP
        PSHA
	    INX
	    STX EVEN
        INCB
        CMPB LENGTH
        BEQ WRITE
        LDX ODD
        BRA BACK
WRITE   CLRB
        LDX NEW
BACK3   PULA
		STAA ,x
        INX
        INCB
        CMPB LENGTH
        BNE BACK3
       .ORG $1200
ARY1   .byte $32,$33,$22,$87
       .end
