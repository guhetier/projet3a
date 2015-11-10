#!/bin/bash

min=100
max=30000
arg=$min

while [ "$arg" -le "$max" ]
do
    echo "Running test with n = "$arg"..."
    r=$(./memoryTest $arg 2>&1)
    echo $r
    echo $r >> result2.txt
    echo -e "Done.\n"
    arg=$(($arg*2))
done
