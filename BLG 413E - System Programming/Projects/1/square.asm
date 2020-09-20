segment .text
	global square
	extern mult			;use exported function

square:
	push ebp          	;save the old base pointer value
	mov  ebp,esp      	;base pointer <- stack pointer
	sub  esp,32
	
	mov  eax,[ebp+16] 	;reverse ordered first argument
	push eax			;first paramter
	mov  eax,[ebp+12] 	;second argument
	push eax			;second paramter
	mov  eax,[ebp+8]	;third argument
	push eax			;third paramter
	mov  eax,[ebp+8]	;fourth argument
	push eax			;fourth paramter
	
	call mult			;call mult function
		
	mov  esp,ebp
	pop  ebp          	;restore base pointer
	ret               	;jump to return address
