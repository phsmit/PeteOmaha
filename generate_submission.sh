#!/bin/bash

rm -Rf subm/
mkdir subm
cp *.h *.c pe/include/*.h pe/lib/*.c pe/lib/*.h subm
cd subm
zip subm.zip *.c *.h
cd ..
