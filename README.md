# Banker's Algorithm

This program implements the banker's algorithm.


## Usage

```
./bankers_algorithm
```


## Program Structure

The program is relatively straightforward and is mostly handled by the `isInSafeState` function that takes a pointer to a safe sequence (originally filled with zeros) and fills it with the safe sequence (if one exits) and then returns a boolean indicating *if* a safe sequence exists.


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

1. Parse input in CSV format from STDIN instead of having it hard-coded.
2. Check output against known test cases.

