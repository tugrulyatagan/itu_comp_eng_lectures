      opt     cre
      org     $400
start
      move.w  sayi1,d0
      add.w   sayi2,d0
      move.w  d0,sonuc
      stop    #$2000

      org     $500  
sayi1 dc.w    $1111 
sayi2 dc.w    $2222 
sonuc ds.w    1     
      end     start  Dosya sonu

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
