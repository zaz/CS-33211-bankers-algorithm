# Banker's Algorithm

This program implements the banker's algorithm.


## Usage

```
./bankers_algorithm [-v] < input_file
```

Where `-v` gives verbose output. The program returns 0 if the system is in a safe state, 1 if it is not.

Run `./bankers_algorithm < tests/given` to run it on the assigned input, or run `make test` to run the full test suite.


## P0: Available Resources

Available resources are stored in P[0], a dummy process whose maximum resources are always 0. For this reason, **I use P[1] - P[5] instead of P[0]-P[4]** to denote the real processes.


## Program Structure

The program contains two functions: `inputTooShort` to assist in handling a recurring kind of error, and `main`. `main` determines if the debug flag `-v` is set, reads from stdin, runs the banker's algorithm, and outputs the results.

The banker's algorithm loops through all real processes (not including P0). If it finds a process that can terminate (the available resources exceed the maximum resources needed by the process), that process is added to the safe sequence and we go back to the start of the loop.


## Input

Input is given on stdin and consists of a buffer of 8-bit integers. The first byte is the number of processes p, the second byte is the number of kinds of resources r. The next p × r bytes represents the allocation of resources, with the first p bytes representing the resources allocated to no process (P0). The first p bytes after 2 + p × r bytes must be 0, as this represents the maximum resources P0 needs, which is always none.

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

The program checks for input that is too short and calls `exit(2)` (avoiding buffer overflow), but doesn't check if it is too long; it simply discards the extra input. The edge cases where we have no processes or no resources are tested. The edge case where even the dummy process P0 is not given is handled with an if statement that calls `exit(3)`. Error exit codes are distinct from `1`, the code returned when the system is not in a safe state.

The program was compiled using GCC 13.2.1 with `-Wall -Wextra` and no warnings were observed.


## Potential Improvements

1. Factor `readInput` and `isInSafeState` functions out of the `main` function to enhance code reusability.
2. Handle interrupts gracefully.
