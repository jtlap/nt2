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

import os
import sys
import re
from archi      import Sse, Vmx
from nt2_base   import Nt2
from fctor      import Functor
from file_utils import read, write, exist, mkdir
from mylogging  import Mylogging
from list_utils import show


class Findintr(Nt2) :
    """ Find simd tags having a proper impl for  given functors in given toolboxes"""
    Toolbox_List = [
        "trigonometric","predicates","ieee","arithmetic","bitwise","fuzzy","hyperbolic",
        "exponential","reduction","elliptic","bessel","combinatorial","euler"]

    def __init__(self, tb_list = None) :
        Nt2.__init__(self)
        if tb_list is None :
            self.tb_list = self.get_all_toolboxes()
        else :
            self.tb_list = tb_list       

    def get_all_toolboxes(self) :
        p = self.absolute_path_to_mode()
        return [ f for f in os.listdir(p) if exist(os.path.join(p,f+'.hpp'))]
      
    def get_list(self) :
        l = []
        for tb_name in self.tb_list :
            name = os.path.join(self.absolute_path_to_mode(),tb_name,tb_name+'.hpp')
            s = read(name)
            r = self.create_txt(s,tb_name)
            l.extend(r)
        return l

    def create_txt(self,s,tb_name) :
        r = []
        for l in s :
            m= re.search('\#include <nt2/toolbox/'+tb_name+'/include/(.*)>',l)
            if m :
                fct_name =m.groups()[0][:-4]
                r.append(fct_name)
        return r    

    def get_simd_propers(self,arch,modes,fcts) :
        for tb_name in self.tb_list :
            for k in modes.keys()[1:] :
                for name in fcts :
                    src = os.path.join(self.absolute_path_to_mode(),tb_name,"function/simd",arch,k,name+'.hpp')
                    if  exist(src) and (os.path.getsize(src) > 1536) :
                        print "in toobox %s in mode %s functor %s has a proper implementation " % (tb_name, k, name)
            
       
if __name__ == "__main__":
    Mylogging.set_level('CRITICAL')
    f = Findintr()#["arithmetic"])
#    l = f.get_list()
#    show(f.get_list())
    show(f.get_simd_propers("sse",Sse.Variants,f.get_list()))
#    show(f.get_includes())
#    show(f.get_unexpected())

