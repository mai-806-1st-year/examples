#!/usr/bin/env sh
cat $(find /cygdrive/d/GitHub/c-utilities \( -name \*.c -o -name \*.gitignore \) -type f -print) | wc -c

for i in $(find ./ -name \*.log -type f -print)
do
    cat "$i" | tr '0123456789' '3456789012' >> "$i"
done

find ./src -name *.c -type f -print
find ./ \( -name \*.c -o -name \*.h \) -type f -print
find ./ -type f -printf 'file: %p\n'
find ./ -type f -printf 'file: %p, size: %s\n'

IFS='&'

for i in $(seq 10)
do
    echo "i = $i"
done


echo $#
echo $0
echo $1
echo $2
echo $3
