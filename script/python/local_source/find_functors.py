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
import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write, exist, mkdir
from mylogging  import Mylogging
from list_utils import show
from recover_sys_toolboxes import Recover

class Find :
    """ Find functors non included in toolboxes"""
    Toolbox_List = [
        "trigonometric","predicates","ieee","arithmetic","bitwise","fuzzy","hyperbolic",
        "exponential","reduction","elliptic","bessel","combinatorial","euler"]
    Pname = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/core/numeric/function/details/scalar'
    Iname = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/nt2/include/functions'

    def __init__(self) :
        pass
    
    def get_list(self) :
        l = []
        for tb_name in Find.Toolbox_List :
            name = os.path.join(Recover.Iname,tb_name+'.hpp')
            s = read(name)
            r = self.create_txt(s)
            l.extend(r)
        return l

    def create_txt(self,s) :
        r = []
        for l in s :
            m= re.search('\#include <nt2/core/numeric/function/(.*)>',l)
            if m :
                fct_name =m.groups()[0][:-4]
                r.append(fct_name)
        return r    

    def get_includes(self) :
        l = []
        for name in os.listdir(Find.Pname) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l

    def get_unexpected(self) :
        u=[]
        expected = self.get_list()
        for l in self.get_includes() :
            if not l in expected :
                u.append(l)
        return u
       
if __name__ == "__main__":
    Mylogging.set_level('CRITICAL')
    f = Find()
#    show(f.get_list())
#    show(f.get_includes())
    show(f.get_unexpected())
sys.path.pop(0)
