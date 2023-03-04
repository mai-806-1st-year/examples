#!/usr/bin/env sh

gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c main.c -o main.o
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c vector.c -o vector.o
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c vector.test.c -o vector.test.o
gcc vector.o vector.test.o -lm -o vector.test.out
gcc main.o vector.o -lm -o main
./vector.test.out
