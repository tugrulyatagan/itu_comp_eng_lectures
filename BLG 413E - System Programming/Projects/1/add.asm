segment .text
	global add

add:
	push ebp          	;save the old base pointer value
	mov  ebp,esp      	;base pointer <- stack pointer
	sub  esp,12			;take 12 byte memory from stack for local variables
	
	mov  eax,[ebp+20]
	mov	 ebx,[ebp+20]
	mul  eax
	mov  ecx,eax
	mov  eax,[ebp+16]
clear:						;clear result matrix
	mov  dword [eax],0
	add  dword eax,4
	dec	 ecx
	cmp  ecx,0
	jne  clear
	
	mov  eax,[ebp+8] 	;first argument
	mov  [esp-4],eax	;first variable
	mov  eax,[ebp+12] 	;second argument
	mov  [esp-8],eax	;second variable
	mov  eax,[ebp+16] 	;third argument
	mov  [esp-12],eax	;third variable
	mov  ecx,[ebp+20]	;fourth argument

	mov  eax,ecx
	mul	 ecx
	mov  ecx,eax

loop:
	dec  ecx			;loop counter
	xor  ebx,ebx		;clear ebx

	mov  eax,[esp-4]
	add  ebx,[eax]		;add matrix1 element
	mov  eax,[esp-8]
	add  ebx,[eax]		;add matrix2 element
	mov  eax,[esp-12]
	mov  [eax],ebx

	add  dword [esp-4],4
	add  dword [esp-8],4
	add  dword [esp-12],4

	cmp  ecx,0
	jne  loop			;loop condition
	
	
	mov  esp,ebp
	pop  ebp          	;restore base pointer
	ret               	;jump to return address
