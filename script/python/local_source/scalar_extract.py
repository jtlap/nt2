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


"""extraction of scalar implementation of a functor from old nt2
   usage:
           scalar_extract.py <fct_name>
   
"""
import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import re
from fctor      import Functor
from file_utils import read,write 
from mylogging  import Mylogging
from list_utils    import show

def get_validate(s) :
    validate_found = False
    beg = -1
    end = -1
    nb= 0
    for i,l in enumerate(s) :
        if not validate_found :
            m = re.match(" *struct validate",l)
            if m :
                validate_found = True
                beg = i-1
        else :
           m1 = re.search("({)",l)
           m2 = re.search("(})",l)
           nbl = len(m1.groups()) if m1 else 0
           nbr = len(m2.groups()) if m2 else 0
           nb += nbl-nbr
           if not nb :
               end = i+1
               return s[beg:end]

def get_call(s):
    call_found = False
    beg = -1
    end = -1
    nb= 0
    for i,l in enumerate(s) :
        if not call_found :
            m = re.match(" *struct call",l)
            if m :
                call_found = True
                beg = i-1
        else :
           m1 = re.search("({)",l)
           m2 = re.search("(})",l)
           nbl = len(m1.groups()) if m1 else 0
           nbr = len(m2.groups()) if m2 else 0
           nb += nbl-nbr
           if not nb :
               end = i+1
               return s[beg:end]

           
if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length >= 2 :
        fct_name = sys.argv[1]
        pname = os.path.join('/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/core/numeric/function/details/scalar',fct_name+'.hpp')
        s = read(pname)
        v =get_validate(s)
        show(v)
        print "*********************"
        c = get_call(s)
        show(c)
    else :
        print __doc__
sys.path.pop(0)
           
       

