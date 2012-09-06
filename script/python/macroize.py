#!/usr/bin/python

import sys

def rtrim(s):
    while( len(s) != 0
           and (s[-1] == '\\'
                or s[-1] == '\n'
                or s[-1] == '\r'
                or s[-1] == ' '
               )
         ):
        s = s[0:-1]
    return s

def main():
    line_size = 80
    if(len(sys.argv) > 1):
        line_size = int(sys.argv[1])

    last = False
    arg = sys.stdin.readline()
    while arg:
        next_arg = sys.stdin.readline()
        if not next_arg:
            last = True

        if last:
            sys.stdout.write(arg)
            return

        arg = rtrim(arg)

        if len(arg) >= line_size:
            sys.stdout.write(arg + '\\' + '\n')
        else:
            sys.stdout.write(arg + (' ' * (line_size - len(arg) - 1)) + '\\' + '\n')

        arg = next_arg

if __name__ == "__main__":
    main()

