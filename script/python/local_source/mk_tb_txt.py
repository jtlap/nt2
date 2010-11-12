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


"""creation of txt generation files from old nt2
   usage:
           mk_tb_txt <tool_box_name> [<path to toolbox>]
   
"""
import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import re
from fctor      import Functor
from file_utils import read,write,exist 
from mylogging  import Mylogging
from list_utils    import show

def get_arity(pname) :
    if exist(pname) :
        s = read(pname)
        r = []
        for l in s :
            m = re.search('  NT2_FUNCTION_IMPLEMENTATION',l)
            if m :
                #            print "l = %s " % l
                m = re.search('([0-9]+)\)',l)
                if m :
                    #                print " arity %s "% m.groups()[0]
                    return m.groups()[0]
    return ""

def create_txt(tb_name,s) :
    r = [ tb_name, " "]
    for l in s :
        m= re.search('\#include <nt2/core/numeric/function/(.*)>',l)
        if m :
            fct_name =m.groups()[0][:-4]
            p=os.path.join('/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/core/numeric/function/',fct_name+'.hpp')
            arity = get_arity(p)
            if arity !="" :
                r.append(fct_name+(30-len(fct_name))*' '+arity)
    return r    




if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length >= 2 :
        tb_name = sys.argv[1]
        pname = os.path.join('/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/include/functions',tb_name+'.hpp')
        s = read(pname)
        s = create_txt(tb_name,s)
        write(tb_name+'.txt',s)
    else :
        print __doc__
sys.path.pop(0)
           
       

