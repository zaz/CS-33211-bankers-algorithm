# compiler flags
flags = -Wall -Wextra

# "all", "clean" and "test" are not files
.PHONY: all clean test watch

# default action
all: producer consumer

# compile producer
bankers_algorithm: bankers_algorithm.c
	gcc $(flags) -o bankers_algorithm bankers_algorithm.c

clean:
	rm -f bankers_algorithm

# compile and run producer
test: bankers_algorithm
	./bankers_algorithm
