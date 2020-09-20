      opt     cre
      org     $400
      
start move.b	boyut,d0

loop1 lea	dizi,a0
      dbeq	d0,devam  
      jmp	son
devam move.l	#0,d1
      move.b	boyut,d1
      subq.b	#2,d1
loop  move.b	(a0)+,d2
      move.b	(a0),d3
      cmp.b	d2,d3
      blt	swap
      dbeq	d1,loop  
      jmp	loop1
swap  lea	(-1,a0),a0
      move.b	d3,(a0)+
      move.b	d2,(a0)
      dbeq	d1,loop        
     jmp	loop1
son      stop    #$2000

      org     $500  
dizi ds.b    	5    
boyut dc.b    	5 

       end     start  Dosya sonu








*~Font name~Courier New~
*~Font size~14~
*~Tab type~1~
*~Tab size~8~
