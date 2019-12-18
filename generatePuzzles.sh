#!/bin/sh
for i in 3 4 5 6 7 8 9 10
do
    python2 puzgen.py "$i" -s > tests/valid/test"$i"
    python2 puzgen.py "$i" -u > tests/invalid/test"$i"
done