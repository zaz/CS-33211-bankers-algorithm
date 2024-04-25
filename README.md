# Banker's Algorithm

This program implements the banker's algorithm.


## Usage

```
./bankers_algorithm [-v] < input_file
```

Where `-v` gives verbose output.

Run `./bankers_algorithm < tests/given` to run it on the assigned input, or run `make test` to run the full test suite.


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

`make test` builds and runs the banker's algorithm on a set of test cases, including the assigned input (`./bankers_algorithm < tests/given`). The fact that the input is binary has the fun side effect that we can pipe ASCII text into our program and see if the corresponding system is in a safe state:

``` bash
$ echo -ne "\b\bIn the beginning the Universe was created. This has made a lot of people very angry and been widely regarded as a bad move. - DA" | ./bankers_algorithm
System is in a safe state.
Safe sequence: P1 -> P2 -> P5 -> P3 -> P4 -> P6 -> P7
```

The above works because `\b` generates an ASCII backspace, which has numeric value 8. So we are telling `bankers_algorithm` that we have 8 processes (including the dummy process P0) and 8 kinds of resources. The 128-character string represents the resource allocation and maximum possible resource allocation. You can see more detailed output with `./bankers_algorithm -v < tests/HHGTTG`

Valgrind confirmed that no memory leaks are possible when the programs exit normally, but handling memory when the program is interrupted was not made robust.

```
==3087== HEAP SUMMARY:
==3087==     in use at exit: 0 bytes in 0 blocks
==3087==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==3087==
==3087== All heap blocks were freed -- no leaks are possible
```


## Robustness

The program checks for input that is too short, but doesn't check if it is too long; it simply discards the extra input.


## Potential Improvements

1. Handle interrupts gracefully.
2. Check that it handles edge cases gracefully (e.g. 0 processes)
