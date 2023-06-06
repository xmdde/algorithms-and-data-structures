# Algorithms and Data Structures
## List 1
Implementation of some data structures:
1. queue and stack
2. singly linked list
3. circular doubly linked list<br>

Implemented merge functions and measuring time accessing elements on different positions in lists.

## List 2 - Sorting algorithms
Implementation of chosen sorting algorithms:
Usage:
```
./chosen_generator sizeOfArrayToSort | ./chosen_sort
```
or to get statistics (total number of swaps and comparisions for different array size written to a file):
```
./chosen_sort -s
```
## List 3 - Selection algorithms, Binary search
Implementation of selection algorithms, binary search.
Usage (to get k-th order statistic):
```
./generator sizeOfArray k [-a] [-d] | ./chosen_algorithm 
```
-a to generate data in ascending order
-d to generate data in descending order

## List 4 - Tree data structures
Usage (to display presentation of insert and delete operations on choosen tree type):
```
./generator k [-a] | ./chosen_tree -p  
```
