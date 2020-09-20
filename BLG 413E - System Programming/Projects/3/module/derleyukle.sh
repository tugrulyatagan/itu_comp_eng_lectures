#!/bin/bash
make
rmmod scull
rm /dev/scull0
insmod ./scull.ko scull_quantum=4096
mknod /dev/scull0 c 250 0
