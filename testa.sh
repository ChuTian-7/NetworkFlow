#!/bin/sh

cd build
make
cd ../testa
./runtests.py --lang lang.json ../build/test/testaTest