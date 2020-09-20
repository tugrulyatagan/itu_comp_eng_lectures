    .ORG $0000
VALUE .byte $84,$12,$83,$14,$0B,$00
CHECK .byte $A3
      .ORG $0010
      LDX #VALUE
      LDAA 0,x
      LDAB 1,x
      PSHA
      PSHB
      LDAA 2,x
      LDAB 3,x
      PSHA
      PSHB
      LDAA 4,x
      LDAB 5,x
      PSHA
      PSHB
      LDAA CHECK
      CMPA #$A4
      BLT SUBST
      BSR SUM
      BRA STOP
SUBST  BSR SUB
       BRA STOP
SUM    CLC
       TSX
       LDAA 5,x
       LDAB 7,x
       STAA $4000
       ADCB $4000
       BCS SETC
BACK   STAB 0,x
       TSX
       LDAA 4,x
       LDAB 6,x
       ABA
       LDX 2,x
       STAA 1,x
       RTS
SETC   LDAA #$01
       LDX 2,x
       STAA 2,x
       BRA BACK

SUB    CLC
       TSX
       LDAA 5,x
       LDAB 7,x
       LDX 2,x
       STAB $4000
       SBCA $4000
       BCS SETC2
BACK2  STAA 0,x
       TSX
       LDAA 6,x
       LDAB 4,x
       SBA
       LDX 2,x
       STAA 1,x
       RTS
SETC2  LDAB #$FE
       STAB 2,x
       BRA BACK2
STOP   .end
