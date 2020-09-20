segment .text
	global scale

scale:
	push ebp          	;save the old base pointer value
	mov  ebp,esp      	;base pointer <- stack pointer
	sub  esp,12
	
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
	mov  eax,[ebp+16] 	;third argument
	mov  [esp-12],eax	;third variable
	mov  ecx,[ebp+20]	;fourth argument
	mov  eax,ecx
	mul	 ecx
	mov  ecx,eax

loop:
	dec  ecx			;counter
	mov  eax,[esp-4]
	mov  eax,[eax]
	mov  edx,[ebp+12]
	mul  edx			;multiply elemnts
	mov  ebx,[esp-12]
	mov  [ebx],eax
	add  dword [esp-4],4
	add  dword [esp-12],4
	cmp  ecx,0
	jne  loop			;loop condition
	
	mov  esp,ebp
	pop  ebp          	;restore base pointer
	ret               	;jump to return address
