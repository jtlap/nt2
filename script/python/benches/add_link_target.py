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


"""User utility to add link targets in usr toolboxes
   usage:
           add_link_target.py <tb_name> target_1 ... target_n

   
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

class Add_Target :
    def __init__(self, tb_name='cephes',
                 mode = 'modify',
                 style='usr') :
        self.__tb_name    = tb_name
        self.__path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox',tb_name)

    def get_tb_name(self)   : return self.__tb_name
    def get_def_path(self)  : return os.path.join(self.__path,'function')
    def get_test_path(self,test_type,mode) : return os.path.join(self.__path,test_type,mode)

    def get_fctors_list(self) :
        l = []
        for name in os.listdir(self.get_def_path()) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l


    ###################################
    # test modifications
    ###################################
    def modify_Cmake_benches_txt(self,test_type,mode,targets) :
        s = self.get_Cmake_benches_txt(test_type,mode)
        s = self.add_targets(s,targets)
#        show(s)
        self.write_Cmake_txt(s,test_type,mode)
        
    
    def get_Cmake_benches_txt(self,test_type,mode) :
        p = os.path.join(self.get_test_path(test_type,mode),'CMakeLists.txt')
        s = read(p)
#        show(s)
        return s
    
    def add_targets(self,s,targets):
        pattern = " *TARGET_LINK_LIBRARIES\(\${EXECUTABLE} nt2\)"
        index = -1
        for i,l in enumerate(s) :
            if re.match(pattern,l) :
                index = i;
                break
        if index >=0 :
            r = []
            for t in targets :
                r.append( "  TARGET_LINK_LIBRARIES(${EXECUTABLE} %s )"%t)
            s = s[:index+1]+r+s[index+1:]
        return s

        
    def write_Cmake_txt(self,s,test_type,mode) :
        print "writing CMakeLists.txt"
        p = os.path.join(self.get_test_path(test_type,mode),'CMakeLists.txt')
        write(p,s,False)
        #show(s)
        return s
 

if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length >= 2 :
        old = Add_Target(sys.argv[1])
        old.modify_Cmake_benches_txt("bench","scalar",sys.argv[2:])
        old.modify_Cmake_benches_txt("bench","simd",sys.argv[2:])
        old.modify_Cmake_benches_txt("unit","scalar",sys.argv[2:])
        old.modify_Cmake_benches_txt("unit","simd",sys.argv[2:])

    else :
#        old = Add_Target("fdlibm")
#        old.remove_simd_dir()
#        old.modify_Cmake_benches_txt("bench","scalar",["nt2_fdlibm"])
#        old.modify_Cmake_benches_txt("bench","simd",["nt2_fdlibm"])
#        old.modify_Cmake_benches_txt("unit","scalar",["nt2_fdlibm"])
#        old.modify_Cmake_benches_txt("unit","simd",["nt2_fdlibm"])
#        old.modify_functors_defs()
        print __doc__

sys.path.pop(0)
           
       

