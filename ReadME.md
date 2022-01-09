This project extracts words from a large string of poetry, then stores words beginning with the same letter inside a spare array of doubly linked lists. 
It then prints out words beginning with the same letter on the same line. 


Algorithm tasks:

1- Split a large string and store individual words into a vector of strings.

2- Use linear search to find and collect words that begin wit the same letter and store them inside the doubly linked list. This list is stored inside the sparse array 
with the index depending on the letter. 

3- The list storing words beginning with the same letter is cleared. 

4- The linked list inside the sparse array are printed if they are not empty. 

Please see the Ex17-6.cpp file for the implementation of this algorithm. 

The doubly linked list, sparse array and std::pair contrainer are all self-made class templates. The doubly linked list is made using the iterator design method.


Linked list features:

1- Doubly linked 

2- Move semantics enabled: move constructor + move and copy assignment operator.

3- Iterator design pattern similar to the STL implementation. 

For other features please check my doubly linked list project. 


HEADER FILES: LinkedList.h , Pair.h, SparseArray.h

MAIN .cpp FILE= Ex17-6.cpp
