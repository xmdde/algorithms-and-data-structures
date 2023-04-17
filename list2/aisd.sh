#!/bin/bash
echo "INSERTION SORT"
for i in 8 16 32
do
./generator $i | ./insertion_sort
./asc_generator $i | ./insertion_sort
./desc_generator $i | ./insertion_sort
done

echo "MERGE SORT"
for i in 8 16 32
do
./generator $i | ./merge_sort
./asc_generator $i | ./merge_sort
./desc_generator $i | ./merge_sort
done

echo "QUICK SORT"
for i in 8 16 32
do
./generator $i | ./quick_sort
./asc_generator $i | ./quick_sort
./desc_generator $i | ./quick_sort
done
