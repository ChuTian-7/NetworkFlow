#!/bin/sh

a=0

cd build
make
cd ..

until [ $a -gt 50 ]
do
  echo "Test $a :"
  ./build/test/bruteforceTest $a
  a=`expr $a + 1`
done