segment .data             ;initialized data definitions
msg db "Hello, world!",10 ;initialized data bytes (10 is ASCII code for newline)
len equ $ - msg           ;length of msg

segment .text             ;the start of a group of instructions to be assembled
global _start             ;entry label for the program

_start:
    mov eax,4             ;write system call
    mov ebx,1             ;output descriptor (standart output)
    mov ecx,msg           ;start of output buffer
    mov edx,len           ;length of output
    int 80h               ;software interrupt 80h to implement the system call

    mov eax,1             ;exit system call
    mov ebx,0             ;return status: success
    int 80h               ;software interrupt 80h to implement the system call
