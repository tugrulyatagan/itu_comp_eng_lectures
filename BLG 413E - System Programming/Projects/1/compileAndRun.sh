#!/bin/bash
rm -f *.o*				#clear old object files
nasm -f elf32 add.asm
nasm -f elf32 sum.asm
nasm -f elf32 mult.asm
nasm -f elf32 scale.asm
nasm -f elf32 square.asm
nasm -f elf32 ITU.asm

gcc -c main.c -o main.o	#compile c file
gcc main.o add.o sum.o mult.o scale.o square.o ITU.o -o hw1.out	#load
./hw1.out				#run
