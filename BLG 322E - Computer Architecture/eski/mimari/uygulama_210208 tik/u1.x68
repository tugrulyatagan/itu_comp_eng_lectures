        ORG     $1000
        MOVE.L  #$A2,D0
        CLR.L   D1
        MOVE.B  data,D1
        ADD.B   D0,D1
        MOVE.B  D1,result
        RTS
        ORG     $2000
data    DC.B    $24
result  DS.B    1
        END     $1000