#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Tools for defining nt2 supported simd architectures 
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import sys
import os
import logging
import re
from nt2_env     import nt2_py_dir
from list_utils  import show


def traversal(root,d) :
    lf = os.listdir(root)
#    print lf
    d[root]=[]
#     print "root %s " %root
    for f in lf :
        d1=os.path.join(root,f)
        if os.path.isdir(d1) and f[0] != '.' :
#             print "d1 %s" %d1
#             print "f %s" %f
            d[root].append(f)
            traversal(d1,d)


if __name__ == "__main__":
    dtroot = os.path.expanduser("~/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/")
##    z= dtstat(dtroot)
##    show(z)
##    print os.listdir(dtroot)
    d={}
    traversal(dtroot,d)
    for k,v in d.items() :
        print "%s -> %s" %(k,v)
