#!/bin/bash

rm -Rf subm/
mkdir subm
cp *.c include/*.h lib/*.c lib/*.h subm
cd subm
zip subm.zip *.c *.h
cd ..
