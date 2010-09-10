#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

"""Tools for playing with toolboxes tree structure
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"


import os
import sys
import string
import re

from file_utils    import write, exist, mkdir
from headerfiles   import Headers
from nt2_base      import Nt2
from mylogging     import Mylogging


class Tb_tree :
    """ creation and deletion of (empty) toolbox trees.
    <root_name>     is the name of the root directory
    <root_abs_path> is the path to the root directory
                    not including it
    <rel_tree>      is the list of path from the root (not
                    including it to be created or deleted)

    
    """
    def __init__(self, root_name, root_abs_path, rel_tree) :
        self.logger = Mylogging("nt2.tb_tree.Tb_tree")
        self.__root_name = root_name
        self.__mk_rel_tree(rel_tree)
        self.__root_abs_path = root_abs_path

    def __mk_rel_tree      (self,tree) :
        self.__rel_tree = []
        for l in  tree :
            self.__rel_tree.append(os.path.join( self.__root_name,l))
        self.__rel_tree.sort()    
    
    def get_root_name    (self) : return self.__root_name
    def get_rel_tree     (self) : return self.__rel_tree
    def get_root_abs_path(self) : return self.__root_abs_path
        
    def show_tb_tree(self) :
        for l in  self.get_abs_tree() :
           print l

    def get_abs_tree(self) :
        r = []
        for l in  self.get_rel_tree() :
           r.append(os.path.join(self.get_root_abs_path(),l))
        return r
           
    def create_tb_tree(self) :
        for l in  self.get_abs_tree() :
           if not exist(l) :
               self.logger.info("\ncreating : \n%s" % l)
               mkdir(l)
           else :
               self.logger.warning("\ndirectory : \n%s\nalready exists" % l)

    def update_tb_tree(self) :
        for l in  self.get_abs_tree() :
           if not exist(l) :
               self.logger.info("\ncreating : \n%s" % l)
               mkdir(l)

    def check_tb_tree(self) :
        for l in  self.get_abs_tree() :
            r = exist(l)
            if not r :
                self.logger.info("\nfile %s does not exist" % fname)
                return False
        return True       

    def remove_tb_tree(self) :
        r = self.get_abs_tree()
        r.reverse()
        for l in r :
            try :
                os.rmdir(l)
                self.logger.info("\ndirectory : \n%s\nhas been removed" % l)
            except (OsError) :
                self.logger.warning("\ndirectory : \n%s\nis not empty, so not removed" % l)

    def get_tb_tree_lack(self) :
        """return the list of non existing directories required for
        defined tree. Returns an empty list if the tree is full.
        """
        r = []
        for l in  self.get_abs_tree() :
            if not exist(l) :
                r.append(l)
        return r
          
if __name__ == "__main__":
    a_tree = [
        "",
        "include",
        "src",   
        "doc",
        "doc/source",
        "unit",
        "unit/scalar",
        "unit/simd",
        "benchmark",
        "benchmark/scalar",
        "benchmark/simd",
        "function",
        "function/scalar",
        "function/simd",
        "function/simd/common",
        "function/simd/vmx", 
        "function/simd/vmx/common_vmx",
        "function/simd/vmx/altivec",
        "function/simd/vmx/spu",
        "function/simd/sse",
        "function/simd/sse/common_sse",
        "function/simd/sse/sse2",
        "function/simd/sse/sse3",
        "function/simd/sse/ssse3",
        "function/simd/sse/sse4_1",
        "function/simd/sse/sse4_2",
        "function/simd/sse/avx",
        "function/simd/sse/sse4a",
        "function/simd/sse/xop",
        "function/simd/sse/fma4",
        ]
    from list_utils import show
    Mylogging.set_level('ALWAYS')
    name = "pipo"
    path = "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox"
    tb = Tb_tree(name,path,a_tree)
    print "get_root_name()      %s   "%tb.get_root_name()        
    print "get_rel_tree()       %s   "%tb.get_rel_tree()    
    print "get_root_abs_path()  %s   "%tb.get_root_abs_path()             
##    tb.show_tb_tree()
##    tb.create_tb_tree()
##    tb.remove_tb_tree()
##    show(tb.get_tree_lack())
    show(tb.get_rel_tree())
