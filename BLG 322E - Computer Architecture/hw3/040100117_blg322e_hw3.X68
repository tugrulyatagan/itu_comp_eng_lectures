*-----------------------------------------------------------
* Title      : Bubble Sort with instruction emulation
* Written by : Tugrul Yatagan   040100117
* Date       : 16/04/2014
* Description: BLG322E Computer Architecture HW3
*-----------------------------------------------------------
    ORG     $1000
START:                      ; first instruction of program
    ; main program
    LEA     STK,A7          ; assign stack pointer initial adress
    ADDA.L  #40,A7          ; stack grows to decreasing address with size 40
    MOVE.L  #SER,($2C)      ; service routine starting adress according to vector table
    DC.W    $F000,0,$2000   ; sortasc $2000
    DC.W    $F001,0,$2100   ; sortdesc $2100
    BRA     FIN             ; terminate program


    ; exception service routine
SER MOVEM.L D1-D4/A0-A3,-(A7) ; move registers to stack for backup
    MOVEA.L 34(A7),A0       ; PC to A0, 34 word difference
    SUB.L   #2,A0           ; adjust A0 to take OpCode as a parameter
    MOVE.W  (A0)+,D1        ; OpCode to D1
    ADD.L   #2,A0           ; adjust A0 to take address of array as a paremeter
    MOVEA.W (A0),A1         ; adress of array to A1
    TST.B   D1              ; sortasc or sortdesc ?
    BNE     DES             ; if sortdesc then branch sortdesc routine
                            ; else sortasc
    ; sortasc
    MOVEA.W A1,A2           ; adress of array to A2
ai  MOVE.B  (A2)+,D2        ; take element A[i] from array to D2
    TST.B   D2              ; is element A[i] equals 0?
    BEQ     RET             ; if it is then end i loop
    MOVEA.W A1,A3           ; adress of array to A2
aj  MOVE.B  (A3)+,D3        ; take element A[j] from array to D3
    MOVE.B  (A3),D4         ; take element A[j+1] from array to D4
    TST.B   D4              ; is element A[j+1] equals 0? end of the array reached
    BEQ     ai              ; if it is then end j loop
    CMP.W   D3,D4           ; compare A[j] and  A[j+1]
    BHI     aj              ; if  A[j] < A[j+1] then skip
    MOVE.B  D3,(A3)         ; if  A[j] > A[j+1] then swap
    SUB.L   #1,A3           ; swap  A[j] and A[j+1]
    MOVE.B  D4,(A3)+        ; swap  A[j] and A[j+1]
    BRA     aj              ; end j loop
    
    ; sortdesc
DES MOVEA.W A1,A2           ; adress of array to A2
di  MOVE.B  (A2)+,D2        ; take element A[i] from array to D2
    TST.B   D2              ; is element A[i] equals 0?
    BEQ     RET             ; if it is then end i loop
    MOVEA.W A1,A3           ; adress of array to A2
dj  MOVE.B  (A3)+,D3        ; take element A[j] from array to D3
    MOVE.B  (A3),D4         ; take element A[j+1] from array to D4 
    TST.B   D4              ; is element A[j+1] equals 0? end of the array reached
    BEQ     di              ; if it is then end j loop
    CMP.W   D3,D4           ; compare A[j] and  A[j+1]
    BLT     dj              ; if  A[j] > A[j+1] then skip
    MOVE.B  D3,(A3)         ; if  A[j] < A[j+1] then swap
    SUB.L   #1,A3           ; swap  A[j] and A[j+1]
    MOVE.B  D4,(A3)+        ; swap  A[j] and A[j+1]
    BRA     dj              ; end j loop 

    ; return from service
RET MOVE.L  A0,22(A7)       ; PC in the stack is updated
    MOVEM.L (A7)+,D1-D4/A0-A3 ; restore used registers
    RTE                     ; return from exception
  
FIN SIMHALT                 ; halt simulator

    ; variables
    ORG $500
STK DS.B 40                 ; memory allocation for stack
    ORG $2000
ARA DC.B $07,$33,$19,$FF,$00 ; array to be ascending sort  
    ORG $2100
ARD DC.B $07,$33,$19,$FF,$00 ; array to be descending sort

    END    START            ; last line of source




*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
