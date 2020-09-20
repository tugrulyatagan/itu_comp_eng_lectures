
      org     $400
start
      move.w  a,d0     A d0 a
      sub.w   b,d0     A-B
      move.b  c,d1     C d1 e
      sub.b   d,d1     C-D
      ext.l   d0       d0 32 bit oldu
      ext.w   d1       d1 16 bit oldu
      divs    d1,d0    iüaretli bîlme
      move.w  d0,sonuc
      swap    d0
      move.w  d0,kalan
      stop    #$2000

      org     $500
a     dc.w    7
b     dc.w    24
c     dc.b    -3
d     dc.b    2
sonuc ds.w    1
kalan ds.w    1
      end     start
