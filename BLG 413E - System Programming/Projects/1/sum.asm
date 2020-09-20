segment .text
	global sum

sum:
	push ebp          	;save the old base pointer value
	mov  ebp,esp      	;base pointer <- stack pointer
	sub  esp,4

	mov  eax,[ebp+8] 	;first argument
	mov  [esp-4],eax	;first variable
	mov  ecx,[ebp+12]	;fourth argument
	mov  eax,ecx
	mul	 ecx			;calculate array lenght
	mov  ecx,eax
	xor  ebx,ebx
	
loop:
	dec  ecx
	mov  eax,[esp-4]
	add  ebx,[eax]		;sum elemnts
	add  dword [esp-4],4
	cmp  ecx,0
	jne  loop
	
	mov  eax,ebx		;return value
	mov  esp,ebp
	pop  ebp          	;restore base pointer
	ret               	;jump to return address
