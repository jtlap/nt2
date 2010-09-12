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


import string

def show(l,empty="input list is empty "):
    """show a list on a line element basis and
    warn for emptyness"""
    if not l :
        print(empty)
    else :
        for ll in l : print ll
    


if __name__ == "__main__":
    l= ['1','2','3','4']
    show(l)
    print "------"
    l = []
    show(l)
    print "------"
    show(l,"")
    print "------"
     
    
