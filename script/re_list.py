#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for automatic generation of some nt2 header files
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2004/05/05 21:57:19 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import re


def sub_list(pattern, repl, stringlist, count=0):
    "apply re.sub to all elements of a list" 
    outlist=[]
    if type(pattern) is str :
      pattern = re.compile(pattern)
    for string in stringlist :
        outlist.append(re.sub(pattern, repl, string, count))
    return outlist

def search_list(pattern, string, flags=None):
    "apply re.search to all elements of a list" 
    outlist=[]
    if type(pattern) is str :
      pattern = re.compile(pattern)
    for string in stringlist :
        outlist.append(re.sub(pattern, string, flags))
    return outlist
