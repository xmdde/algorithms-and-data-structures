#!/bin/bash
for ((i=100; i<=10000; i+=100))
do
for ((j=1; j<=100; j+=1))
do
./generator $i 0 | ./select -e
done
done