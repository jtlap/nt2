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


"""User utility to suppress simd def in usr toolboxes
   usage:
           modify_defs.py <tb_name>

   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write,exist
from mylogging  import Mylogging
#from scalar_extract import get_validate, get_call
from list_utils import show
from re_list    import sub_list
from shutil     import rmtree

class Sup_simd :
    def __init__(self, tb_name='cephes',
                 mode = 'modify',
                 style='usr') :
        self.__tb_name    = tb_name
        self.__path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox',tb_name)

    def get_tb_name(self)   : return self.__tb_name
    def get_def_path(self)  : return os.path.join(self.__path,'function')
    def get_bench_path(self) : return os.path.join(self.__path,'bench') 
    def get_fctors_list(self) :
        l = []
        for name in os.listdir(self.get_def_path()) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l

    ###################################
    # def modifications
    ###################################
    def modify_functors_defs(self) :
        for fctr in self.get_fctors_list():
            self.modify_functors_def(fctr)
            
    def modify_functors_def(self,fct_name) :
        s = self.get_def(fct_name)
        s = self.comment_simd_def(s)
        self.write_def_impl(fct_name,s)

    def get_def(self,fct_name) :
        p = os.path.join(self.get_def_path(),fct_name+'.hpp')
        s = read(p)
        #        show(s)
        return s
        
    def write_def_impl(self,fct_name,s) :
        p = os.path.join(self.get_def_path(),fct_name+'.hpp')
        #write(p,s,False)
        show(s)
        return s
    
    def comment_simd_def(self,s):
        pattern = "^#include NT2_"+self.get_tb_name().upper()
        rep = "// "+pattern[1:]
        return sub_list(pattern,rep,s)

    ###################################
    # bench modifications
    ###################################
    def modify_Cmake_benches_txt(self) :
        s = self.get_Cmake_benches_txt()
        s = self.rep_unit(s)
        self.write_Cmake_txt(s)
        
    
    def get_Cmake_benches_txt(self) :
        p = os.path.join(self.get_bench_path(),'CMakeLists.txt')
        s = read(p)
        #        show(s)
        return s
    
    def rep_unit(self,s):
        pattern = "\.unit"
        rep = ".bench"
        return sub_list(pattern,rep,s)
        
    def write_Cmake_txt(self,s) :
        p = os.path.join(self.get_bench_path(),'CMakeLists.txt')
        #write(p,s,False)
        show(s)
        return s
    
 
    def remove_simd_dir(self):
        p = os.path.join(self.get_def_path(),'simd')
        print p


if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
        old = Sup_simd(sys.argv[1])
        old.remove_simd_dir()
        old.modify_Cmake_benches_txt()
        old.modify_functors_defs() 
    else :
        old = Sup_simd("gsl_specfun")
//        old.remove_simd_dir()
//        old.modify_Cmake_benches_txt()
        old.modify_functors_defs()
        print __doc__

sys.path.pop(0)
           
       

