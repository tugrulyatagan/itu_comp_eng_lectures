      opt     cre
      org     $400
start
      lea	dizi,a0
      move.w	boyut,d0
      move.w	(a0),d1		maximum d1 saklayýcýsýnda
      subq.w	#1,d0
      lea	(2,a0),a0
loop	move.w	(a0)+,d2
      cmp.w 	d2,d1
      blt	swap
*      subq	#1,d0
*      tst.w	d0
*      bne	loop      
      dbeq	d0,loop
      jmp son

swap  move.w	d2,d1
*      subq	#1,d0
*      tst.w	d0
*      bne	loop
      dbeq	d0,loop
      jmp son
son     stop    #$2000

      org     $500  
dizi ds.w    3    
boyut dc.w    3 
       end     start  Dosya sonu






*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~8~
