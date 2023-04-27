#!/bin/bash
for ((i=1000; i<=100000; i+=1000))
do
./generator $i 0 | ./binsearch -s
done

for ((i=1000; i<=100000; i+=1000))
do
./generator $i 0 | ./binsearch -e
done
