#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
##############################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################


"""utilities to substitute strings
   chains to be substitued are of the form <token>.*<token>
   the .* must correspond to an attribute of the class inheiting from
   substitute
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import re

def listify(x) :
    if isinstance(x,str) :
        return [x]
    elif x is None :
        return x
    else :
        return x

def stringize(x,sep=', ') :
    if isinstance(x,str) :
        return x
    elif x is None :
        return x
    else :
        return sep.join(x)

class Substitute(object) :
    def __init__(self) :
        pass

    def keys_of(self,txt,tokenl='\$',tokenr='\$') :
        m = list(set(re.findall('(%s.*?%s)'%(tokenl,tokenr),txt)))
        z = [ mm.replace('$','\$') for mm in m]
        return z

    def replace(self,txt,keys=None,tokenl='\$',tokenr='\$') :
        if keys is None : keys = self.keys_of(txt,tokenl,tokenr)
        ll=len(tokenl)
        lr=-len(tokenr)
        for k in keys :
##            print("k -> %s "%k)
##            print("g -> %s "%getattr(self,k[ll:lr]))
            txt = re.sub(k,getattr(self,k[ll:lr]),txt)
        return txt


if __name__ == "__main__" :
    pass

