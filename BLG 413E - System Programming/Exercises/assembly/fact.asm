segment .text
global fact

fact:
    push ebp
    mov  ebp,esp
    sub  esp,4

    mov  dword [ebp-4],1
    mov  ecx,[ebp+8]
back:
    mov  eax,[ebp-4]
    mul  ecx
    mov  [ebp-4],eax
    dec  ecx
    cmp  ecx,1
    jne  back

    mov  eax,[ebp-4]
    mov  esp,ebp
    pop  ebp
    ret
