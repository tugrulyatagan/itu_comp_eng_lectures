#! /bin/bash
fusermount -u encoded
rm rofs
gcc rofs.c -o rofs -ansi -w -std=c99 -g -ggdb -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -lfuse -liconv
./rofs -d original/ encoded/


