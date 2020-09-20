segment .text
	global ITU

segment .data
	itu				dd  0,0,0,0,0,0,0,0,0,0,0,\
						0,0,0,0,0,0,0,0,0,0,0,\
						0,0,0,0,0,0,0,0,0,0,0,\
						0,1,0,1,1,1,0,1,0,1,0,\
						0,1,0,0,1,0,0,1,0,1,0,\
						0,1,0,0,1,0,0,1,0,1,0,\
						0,1,0,0,1,0,0,1,0,1,0,\
						0,1,0,0,1,0,0,1,1,1,0,\
						0,0,0,0,0,0,0,0,0,0,0,\
						0,0,0,0,0,0,0,0,0,0,0,\
						0,0,0,0,0,0,0,0,0,0,0	;ITU figure
	basize			dd	11			;ITU figure size
	
	ituAdd			dd	0			;address of figure
	resultMat		dd	0			;address of result
	size			dd	0
	scale			dd	0
	leftUpMargin	dd	0
	rightDownMargin	dd	0
	beginPoint		dd	0
	beginAdd		dd	0
	cursor			dd	0			;current position
	cellCounterC	dd 	0
	cellCounterR	dd	0
	genelCounterC	dd	0
	genelCounterR	dd	0
	ituIndex		dd	0
	resultIndex		dd	0
	rowSize			dd	0
	
	
ITU:
	push ebp          				;save the old base pointer value
	mov  ebp,esp      				;base pointer <- stack pointer

	mov  eax,[ebp+12]
	mov	 ebx,[ebp+12]
	mul  eax
	mov  ecx,eax
	mov  eax,[ebp+8]
clear:								;clear result matrix
	mov  dword [eax],0
	add  dword eax,4
	dec	 ecx
	cmp  ecx,0
	jne  clear

	mov  eax,[ebp+8]  				;first argument
	mov  [resultMat],eax
	mov  eax,[ebp+12] 				;second argument
	mov  [size],eax
	
	xor  edx,edx
	div  dword [basize]
	mov  [scale],eax				;scale
	mov  eax,edx
	mov  dword ecx,2
	xor  edx,edx
	div  ecx
	mov  [leftUpMargin],eax			;left,up margin
	add  eax,edx
	mov  [rightDownMargin],eax		;right,down margin
	mov  ebx,[leftUpMargin]
	mov  eax,[size]
	mul  ebx
	add  eax,ebx
	mov  dword ebx,4
	mul  ebx
	mov  dword [beginPoint],eax		;calculate begin point
	mov	 eax,[beginPoint]
	mov  ebx,[resultMat]
	add  eax,ebx
	mov	 dword [beginAdd],eax		;calculate begin address
	mov  dword ebx,[size]
	mov  dword eax,4
	mul	 ebx
	mov  dword [rowSize],eax
	mov  eax,itu
	mov  [ituAdd],eax
	
	mov	 dword [genelCounterR],0	; reset genelCounterR
lh:	;figure row loop
	mov  ebx,[genelCounterR]
	mov  eax,[rowSize]
	mul  ebx
	mov  ebx,[scale]
	mul  ebx
	add  eax,[beginAdd]
	mov  [cursor],eax
	
	mov	 dword [genelCounterC],0	;reset genelCounterC
lg:	;figure coloumn loop
	mov  dword [cellCounterC],0		;reset cellCounterC
lc:	;cell coloumn loop
	mov  dword [cellCounterR],0		;reset cellCounterR
	mov  eax,[cursor]
lr:	;cell row loop
	mov  ecx,[ituAdd]
	mov  ebx,[ecx]
	mov  dword [eax],ebx			;write result
	add  eax,[rowSize]
	add  dword [cellCounterR],1
	mov  ecx,[cellCounterR]
	cmp  ecx,[scale]
	jne  lr							;cell row loop condition
	
	add  dword [cursor],4
	add  dword [cellCounterC],1
	mov  ecx,[cellCounterC]
	cmp  ecx,[scale]
	jne  lc							;cell coloumn loop condition
	
	add  dword [ituAdd],4
	add  dword [genelCounterC],1
	mov  ecx,[genelCounterC]
	cmp  ecx,[basize]
	jne  lg							;figure coloumn loop condition

	add  dword [genelCounterR],1
	mov  ecx,[genelCounterR]
	cmp  ecx,[basize]
	jne  lh							;figure row loop condition

	mov  esp,ebp
	pop  ebp          				;restore base pointer
	ret               				;jump to return address
