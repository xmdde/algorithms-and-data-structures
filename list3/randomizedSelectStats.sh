#!/bin/bash
for ((i=100; i<=10000; i+=100))
do
./generator $i 0 | ./randomized_select -s
done
