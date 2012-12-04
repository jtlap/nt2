#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for showing list of strings
   debug usage
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

__all__ = ['show']

import string

def show(l,empty="input list is empty "):
    """show a list on a line element basis and
    warn for emptyness"""
    if not l :
        print(empty)
    elif type(l) is list :
        for ll in l : print ll
    elif type(l) is dict :
        for k,v in l.items() : print "%s -> %s" %(k,v)



if __name__ == "__main__":
    l= ['1','2','3','4']
    show(l)
    print "------"
    l = []
    show(l)
    print "------"
    show(l,"")
    print "------"


