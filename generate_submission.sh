#!/bin/bash

rm -Rf subm/
mkdir subm
cp *.h *.c pe/include/*.h pe/lib/*.c pe/lib/*.h subm
cd subm
gcc -Wall -Wextra -o test *.c
zip subm.zip *.c *.h
cd ..
