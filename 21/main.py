#!/usr/bin/env python

from os import walk
from os.path import getsize
from os.path import join
from sys import argv

def main(root: str, recursive: bool, max_size: int, out_name: str):
    with open(out_name, 'wb') as out_file:
        for (dirpath, dirnames, filenames) in walk(root):
            for filename in filenames:
                in_name = join(dirpath, filename)
                max_size -= getsize(in_name)
                if max_size < 0:
                    return
                with open(in_name, 'rb') as in_file:
                    out_file.write(in_file.read())
            if not recursive:
                return


if __name__ == '__main__':
    root = argv[1]
    main(root, False, 4096, 'out.txt')
