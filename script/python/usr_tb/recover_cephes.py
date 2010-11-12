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


"""User utility to recover functor(s) from old Nt2
   usage:
           recover_functor @<data_file_name>

   <data_file_name> is the name of a text file the contain of which is:

          <tool_box_name>
          <functor_name_1> [arity_1]
            ...
          <functor_name_n> [arity_n]

          in this case, all the n functors will be added to the toolbox.
          Note: empty of fully blank lines are ignored
   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write
from mylogging  import Mylogging
from scalar_extract import get_validate, get_call
from list_utils import show

def insert_validate_and_call(d,v,c, style, tb_name) :
    if c is not None :
        d = d[:20] + c[4:]+d[27:]
    if v is not None :
        v[0]= "  template<class Info>"
        v[1]= "  struct validate<"
        if style == 'usr' :
            v[1] += tb_name+"::"
        v[1] += fct_name+"_,tag::scalar_(tag::arithmetic_),Info>"
        d = d[:14]  + v + d[14:]
    else :
        d = d[:14]  + ["  //  no special validate for %s" % fct_name, ""] + d[14:]
    return d

def set_one(fct,fct_name,arity,pname) :
    s = fct.read_functor(fct_name,'scalar')
    print "adding functor %s of arity %d" % (fct_name, arity) 
    src = os.path.join(pname,fct_name+'.hpp')
    d = read(src)
    v = get_validate(d)
    c = get_call(d)
    s = insert_validate_and_call(s,v,c,fct.get_tb_style(),fct.get_tb_name())
    show(s)
    fct.write_functor(fct_name,'scalar',s,False)
    
def modify_toolbox(tb_name) :
    fct = Functor(tb_name,mode='modify')
    print ("opening toolbox %s" %fct.get_tb_name())+ \
          " with %s mode" % fct.get_tb_mode()
    return fct


if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
        # this is old nt2 scalar functors dir
        pname = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/toolbox/cephes/function/details/scalar'
        data_file_name = sys.argv[1][1:] 
        s = read(data_file_name)
        tb_name = s[0]
        fct = modify_toolbox(tb_name)
        for ss in s[1:] :
            ss = re.sub('\b',' ',ss)
            if len(ss) == 0 : continue
            l = ss.split()
            if len(l) == 0 : continue
            fct_name = l[0]
            arity = 1 if len(l) <=1 else int(l[1])
            set_one(fct,fct_name,arity,pname)
    else :
        print __doc__
sys.path.pop(0)
           
       

