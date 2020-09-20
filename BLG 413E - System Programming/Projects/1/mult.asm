segment .text
	global mult

mult:
	push ebp          		;save the old base pointer value
	mov  ebp,esp      		;base pointer <- stack pointer
	sub  esp,24				;take 12 byte memory from stack for local variables
	
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

	mov  eax,[ebp+8] 		;first argument
	mov  [esp-4],eax		;first variable
	mov  eax,[ebp+12] 		;second argument
	mov  [esp-8],eax		;second variable
	mov  eax,[ebp+16] 		;third argument
	mov  [esp-12],eax		;third variable
	mov  dword [esp-16],0	;first index
	mov  dword [esp-20],0	;second index
	mov  dword [esp-24],0	;third index


l1:	;matrix loop
	mov  dword [esp-20],0
	mov  eax,[ebp+12] 	
	mov  [esp-8],eax	

l2:	;addition loop
	mov  eax,[ebp+8]
	mov  [esp-4],eax
	mov  ecx,[esp-16]
	mov  eax,[ebp+20]
	mov  dword ebx,4
	mul  ebx				;calculate address
	mul  ecx
	add  [esp-4],eax
	mov  dword [esp-24],0	;third index
	
l3:	;multiplication loop
	mov  ecx,[esp-24]
	mov  eax,[esp-4]
	mov  eax,[eax]
	mov  ebx,[esp-8]
	mov  ebx,[ebx]
	mul  ebx			;multiplication
	mov  ebx,[esp-12]
	add  [ebx],eax
	add  dword [esp-4],4
	mov  eax,[ebp+20]
	mov  dword ebx,4
	mul  ebx			;calculate address
	add  dword [esp-8],eax
	inc  ecx
	mov  [esp-24],ecx
	cmp  ecx,[ebp+20]
	jne  l3				;addition loop condition

	add  dword [esp-12],4
	add  dword [esp-20],1
	mov  ecx,[esp-20]
	mov  ebx,[ebp+12]
	mov  edx,4
	mov  eax,ecx
	mul  edx
	add  ebx,eax
	mov  [esp-8],ebx
	cmp  ecx,[ebp+20]
	jne  l2				;multiplication loop
	
	
	add  dword [esp-16],1
	mov  ecx,[esp-16]
	cmp  ecx,[ebp+20]
	jne  l1				;matrix loop
		
son:	
	mov  esp,ebp
	pop  ebp          	;restore base pointer
	ret               	;jump to return address
