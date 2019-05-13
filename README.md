# sorter
Another code-test interview problem

Can You Sort?
An array of integers arr, of size n is defined as [a[0], a[1], ..., a[n-1]. You will be given an array of integers to sort. Sorting must first be by frequency of occurrence, then by value. For instance, given an array [4, 5, 6, 5, 4, 3], there is one each of 6's and 3's, and there are two 4's, two 5's. The sorted list is [3, 6, 4, 4, 5, 5].

Function Description
Complete a custom sort function. The function must print each element on a separate line, sorted ascending first by frequency of occurrence, then by value within frequency.


To make:
   make [release|debug]

To clean:
   make clean

To run:
   ./build/sorter input.txt 2>&1 | tee output.txt

To test:
   diff output expected-output.txt
