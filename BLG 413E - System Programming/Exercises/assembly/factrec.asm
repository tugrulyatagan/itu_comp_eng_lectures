segment .text
global fact

fact:
    push ebp
    mov  ebp,esp

    mov  eax,1
    mov  ecx,[ebp+8]
    cmp  ecx,1
    je   end_rec

    push ecx

    dec  ecx
    push ecx
    call fact
    add  esp,4

    pop  ecx
    mul  ecx

end_rec:
    pop  ebp
    ret
