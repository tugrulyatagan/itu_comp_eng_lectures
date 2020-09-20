segment .data
k    dd   5
intf db   "%d",10,0

segment .bss
f    resd 1

segment .text
global main
extern printf

fact:
    push ebp
    mov  ebp,esp

    mov  dword [f],1
    mov  ecx,[ebp+8]
back:
    mov  eax,[f]
    mul  ecx
    mov  [f],eax
    dec  ecx
    cmp  ecx,1
    jne  back

    pop  ebp
    ret

main:
    push ebp
    mov  ebp,esp

    push dword [k]
    call fact
    add  esp,4

    push dword [f]
    push intf
    call printf
    add  esp,8

    pop  ebp
    ret
