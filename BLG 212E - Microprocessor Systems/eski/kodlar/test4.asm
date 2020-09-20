	ldaa #4 ;load num 4
	ldaa 4 ;load Mem[4] 
	ldaa #a ;load .equ 6
	ldaa a ;load Mem[#a] 
	ldaa #b ;load addr of b
	ldaa b ;load Mem[#b] 
	ldaa #c ;load a .equ 6 
	ldaa c ;load Mem[#c] 
	ldaa #d ;load addr of b
	ldaa d ;load Mem[#d]
a 	.equ 6 
b 	.byte 6 
c   .equ a ;a = 6
d   .equ b ;addr of b!!