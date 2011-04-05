#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-

"""Tools for iterables
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2004/05/05 21:57:19 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

__all__ = ["iter_flatten"]

def flatten(r):
    if isinstance(r, (list, tuple)):
        for element in r:
            for e in flatten(element) :
                yield e
    else:
        yield r


if __name__ == "__main__":
    pass
    
   
