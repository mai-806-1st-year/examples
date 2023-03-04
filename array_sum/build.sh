#!/usr/bin/env sh

gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c --include-directory=../vector --include-directory=./ array_sum.c -o array_sum.o
gcc -Wall -Werror -Wextra -Wfatal-errors -Wpedantic -pedantic-errors -std=c18 -c --include-directory=../vector --include-directory=./ array_sum.test.c -o array_sum.test.o
gcc array_sum.o array_sum.test.o ../vector/vector.o -lm -o array_sum.test.out
./array_sum.test.out
