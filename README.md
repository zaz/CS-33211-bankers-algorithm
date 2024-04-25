# Banker's Algorithm

This program implements the banker's algorithm.


## Usage

```
./bankers_algorithm < input_file
```


## Program Structure

The program is relatively straightforward and is mostly handled by the `isInSafeState` function that takes a pointer to a safe sequence (originally filled with zeros) and fills it with the safe sequence (if one exits) and then returns a boolean indicating *if* a safe sequence exists.


## Input

Input is given on stdin and consists of a buffer of 8-bit integers. The first byte is the number of processes p, the second byte is the number of kinds of resources r.  The next p × r bytes represents the allocation of resources, with the first p bytes representing the resources allocated to no process. I represent this as "P0", and it is not an actual process. The first p bytes after 2 + p × r bytes must be 0, as this represents the maximum resources P0 needs, which is always none.

```
6 3
3 3 2
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
0 0 0
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```
Spaces above are used for clarity. The actual input file is unspaced, unsigned 8-bit integers.


## Testing

Run `make test` to build and run the banker's algorithm.

Valgrind confirmed that no memory leaks are possible when the programs exit normally, but handling memory when the program is interrupted was not made robust.

```
==3087== HEAP SUMMARY:
==3087==     in use at exit: 0 bytes in 0 blocks
==3087==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==3087==
==3087== All heap blocks were freed -- no leaks are possible
```


## Potential Improvements

1. Check output against known test cases.
