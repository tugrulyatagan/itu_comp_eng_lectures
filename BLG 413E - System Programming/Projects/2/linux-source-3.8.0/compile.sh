#!/bin/bash
make-kpkg clean
#export CLEAN_SOURCE=no
#export CONCURRENCY_LEVEL=8
time fakeroot make-kpkg --initrd --append-to-version=-custom kernel_image kernel_headers
