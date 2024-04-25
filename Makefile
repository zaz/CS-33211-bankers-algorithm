# compiler flags
flags = -Wall -Wextra

# "all", "clean" and "test" are not files
.PHONY: all clean test watch

# default action
all: bankers_algorithm

# compile producer
bankers_algorithm: bankers_algorithm.c
	gcc $(flags) -o bankers_algorithm bankers_algorithm.c

clean:
	rm -f bankers_algorithm

# compile and run producer
test: bankers_algorithm
	diff -U 3 tests/given.out <(./bankers_algorithm < tests/given)
	diff -U 3 tests/HHGTTG.out <(./bankers_algorithm < tests/HHGTTG)
