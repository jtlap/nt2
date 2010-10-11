#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for knowing the current function name
   and the caller name
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import os
import sys
import string
import inspect


def whoami():
    """ return the current funcion name"""
    return inspect.stack()[1][3]

def whosdad():
    """return the caller name or
       return None if called from a <module>
       """
    try :
        return inspect.stack()[2][3]
    except IndexError :
        return None

def whosfile() :
    """return the file name"""
    return __name__

if __name__ == "__main__":
    print "I am      %s"%whoami()
    print "My dad is %s" %whosdad()
    def pipo() :
        print "I am        %s"%whoami()
        print "My dad is   %s" %whosdad()
        print "My file is  %s" %whosfile()
    pipo()
    def zorro() :
        pipo()
    zorro()
    
