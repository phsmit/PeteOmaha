#!/bin/bash

rm -Rf subm/
mkdir subm
cp include/*.h lib/*.c pe/include/*.h pe/lib/*.c pe/lib/*.h programs/peteomaha.c subm
cd subm
gcc -Wall -Wextra -o test *.c
zip subm.zip *.c *.h
cd ..
