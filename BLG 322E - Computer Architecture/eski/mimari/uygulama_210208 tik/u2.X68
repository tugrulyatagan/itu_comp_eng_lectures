*-----------------------------------------------------------
* Program Number:
* Written by    :
* Date Created  :
* Description   :verilen dizinin tersten yazilmasi
*
*-----------------------------------------------------------
	ORG	$1000
dizi	dc.b	'otomata'
ters	ds.b	7
size	dc.b	7
start	lea	dizi,a0
	movea.l	a0,a1
	move.b	size,d0
	rol.l	#1,d0
	add.l	d0,a1
loop	move.b	(a0)+,-(a1)
	cmp	a0,a1
	bgt	loop
	STOP	#$2000
	end	start



	
	
