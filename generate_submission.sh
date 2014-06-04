#!/bin/bash

rm -Rf subm/
mkdir subm
cp include/*.h lib/*.c vendor/*/include/*.h vendor/*/lib/*.c vendor/*/lib/*.h programs/peteomaha.c subm
cd subm
gcc -Wall -Wextra -o test *.c
zip subm.zip *.c *.h
cd ..
