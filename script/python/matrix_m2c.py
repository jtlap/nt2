#!/usr/bin/python

import sys
import re

def horzcat(a, b):

  if(len(a) == 0):
    return b
  if(len(b) == 0):
    return a

  if(len(a) != len(b)):
    raise Exception("Invalid matrix", a, b)

  c = a;
  for i in range(len(b)):
      c[i] += b[i]

  return c

def main():

    tab_local = []
    tab = []
    rows = 0

    coltest = re.compile("^ *Columns? [0-9]+( through [0-9]+)? *$")

    arg = sys.stdin.readline()
    while arg:

      # if columns are spread out, we reset the local tab
      if(coltest.match(arg)):
        tab = horzcat(tab, tab_local)
        tab_local = []
        rows = 0
        arg = sys.stdin.readline()
        continue

      values = arg.split()
      l_rows = len(values)
      if(l_rows == 0):
        arg = sys.stdin.readline()
        continue
      if(rows and l_rows != rows):
        raise Exception("Invalid matrix", rows, l_rows)
      rows = l_rows
      tab_local.append(values)
      arg = sys.stdin.readline()

    tab = horzcat(tab, tab_local)

    rows = len(tab[0])
    cols = len(tab)

    # find max len of each column
    maxlen = []
    for j in range(cols):
      maxlen.append(0)
      for i in range(rows):
        l = len(tab[j][i])
        if(l > maxlen[j]):
          maxlen[j] = l

    # print it C-style
    sys.stdout.write("{\n")
    for i in range(rows):
      sys.stdout.write("  { ")
      
      for j in range(cols):
        for k in range(maxlen[j]-len(tab[j][i])):
          sys.stdout.write(' ')
        sys.stdout.write(tab[j][i])
        if(j != cols-1):
          sys.stdout.write(", ")
      sys.stdout.write(" }")
      if(i != rows-1):
        sys.stdout.write(",")
      sys.stdout.write("\n")
    sys.stdout.write("}\n")


if __name__ == "__main__":
    main()
