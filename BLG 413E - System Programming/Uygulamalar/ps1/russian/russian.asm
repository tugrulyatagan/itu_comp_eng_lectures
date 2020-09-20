segment .text
global russian

russian:
    push ebp          ;save the old base pointer value
    mov  ebp,esp      ;base pointer <- stack pointer

    mov  ecx,[ebp+8]  ;first argument
    mov  edx,[ebp+12] ;second argument
    xor  eax,eax      ;clear eax (used for returning the result)
next:
    shr  ecx,1        ;divide the number on the 1st column by 2
    jnc  even         ;even number (no carry) on the 1st column
    add  eax,edx      ;odd number: add the 2nd column to the result
even:
    shl  edx,1        ;multiply the number on the 2nd column by 2
    cmp  ecx,0        ;stop when the number on the 1st column becomes 0
    jne  next         ;continue if it is not 0

    pop  ebp          ;restore base pointer
    ret               ;jump to return address
