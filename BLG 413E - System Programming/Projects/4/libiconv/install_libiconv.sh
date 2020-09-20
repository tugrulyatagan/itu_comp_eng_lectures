#! /bin/bash
wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.13.1.tar.gz
tar -xzvf libiconv-1.13.1.tar.gz
cd libiconv-1.13.1
./configure --prefix=/usr
make
make install
ldconfig
