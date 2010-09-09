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

"""Tools for creating nt2 toolboxes templates
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

from file_utils    import read, write, exist, mkdir
from headerfiles   import Headers
from nt2_base      import Nt2
from mylogging     import Mylogging
from tb_files      import Tb_files

class Toolbox(Nt2,Tb_files) :
    Tb_tree = [
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
        "function/simd/vmx/common",
        "function/simd/vmx/altivec",
        "function/simd/vmx/spu",
        "function/simd/sse",
        "function/simd/sse/common",
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
    Tb_files =                 {
        "" : {
            "py_data"      : "py_data.py", 
            "base"         : "$root_name$",  
            "root"         : "$root_name$",
            "root_include" : "include.hpp",
            },
        "benchmark" :            {
            "inner"        : "CMakelists.txt"
            },
        "benchmark/scalar" : {
            "scalar"       : "CMakelists.txt"
            },
        "benchmark/simd" :   {  
            "simd"         : "CMakelists.txt",
            },
        "unit" :                 {
            "inner"        : "CMakelists.txt"
            },
        "unit/scalar" :      {
            "scalar"       : "CMakelists.txt"
            },
        "unit/simd" :        {  
            "simd"         : "CMakelists.txt",
            },
         }
    def __init__(self, tool_box_name,
                 mode = 'create',
                 p2nt2 = None,
                 style = 'usr') :

        """creation or recovery of a toolbox
         <tool_box_name> is the name of the toolbox

         <mode> is the opening mode. Proper modes are create(default) or modify

             create : creates a new toolbox tree under .../nt2/toolbox/
                  with the given <tool_box_name> provided that a 
                  directory of this name not existed previously (default)
             update : add all missing directories or files to an existing
                      toolbox without modifying any existing files or
                      directories
             modify : creates a new toolbox tree or allow access to an
                  existing one to add or suppress functors extensions

          <p2nt2> is the path to nt2. The path defaults to the computation 
                  furnished by the Nt2 class
          <style> determines if the functors defined in the toolbox functors
                  will reside in the namespace nt2 ('sys') or in the namespace
                  <tool_box_name> ('usr'). It is only needed when mode is  
                  'create' and is 'usr' by default. The other modes recover
                  the creation parameter from existing data: in the present
                  implementation, once created the toolbox mode cannot be
                  modified.
        """

        Mode = [ 'create', 'update', 'check', 'modify']
        Style = ['usr','sys']
        Nt2.__init__(self,'toolbox')
        self.__status = True
        self.logger = Mylogging("nt2.toolbox.Toolbox")
        if p2nt2 is None : p2nt2 = self.get_path2nt2()
        self.__tb_name     = tool_box_name
        self.__tb_pathfnt2 = os.path.join(self.get_pathfnt2(),self.__tb_name)
        self.__tb          = os.path.join(self.get_path2nt2(),self.__tb_pathfnt2)
        self.__tb_path2mode= os.path.join(self.get_path2nt2(),self.get_pathfnt2())
        self.__tb_style = style if style == "sys" else "usr"
        self.__test_status = True
        self.__mode = mode
        self.__tb_tree = Toolbox.Tb_tree
        self.__tb_files= Toolbox.Tb_files
        Tb_files.__init__(self,self.__tb_name,self.__tb_path2mode,
                          self.__tb_tree,
                          self.__tb_files,
                          style)
        if mode in Mode :
            self.logger.info(
                ("\nopening toolbox %s with mode: "% self.__tb_name) +
                mode+"\nin directory\n" +
                self.__tb
                )
            action = getattr(self,mode+'_tbox')
            action()
        else:
            self.logger.error(
                "\nopening with unknown mode: "+mode+"\n"+
                " raising SystemExit\n"
                )
            raise SystemExit

    def get_tb_name(self) : return self.__tb_name
    def get_tb_pathfnt2(self) : return self.__tb_pathfnt2
    def get_tb_abs_path(self) : return self.__tb 
    def get_tb_path2mode(self) : return self.__tb_path2mode
    def get_status(self) : return self.__status
    def get_tb_style (self) : return self.__tb_style
    def get_tb_namespace(self) :
        return "functors" if (self.__tb_style == "sys") else self.__tb_name 
    def get_tb_mode(self) : return self.__mode
    def get_tb_status(self) : return self.__status
    def get_tb_tree(self) : return self.__tb_tree
    def get_tb_files(self) : return self.__tb_files

    def create_tbox(self):
        """ create a toolbox tree and global files only if it does not exist"""
        if os.path.exists(self.get_tb_abs_path()) :
            self.__status = False
            self.logger.error(
                "\ntoolbox %s already exists\n" % self.get_tb_name() +
                "in path: %s\n" % self.get_tb_abs_path() +
                "please use another toolbox name\n" +
                "or delete the old one using remove_tbox "
                "before creating the new one\n"
                )
            raise SystemExit
        else:
            self.create_tb_tree()
            self.create_tb_files()
        return self.__status

    def update_tbox(self):
        """ add missing directory and files to a toolbox
            without modifying any existing ones
        """
        self.read_style()    
        self.update_tb_tree()
        self.update_tb_files()
        return self.__status

    def check_tbox(self):
        """ add missing directory and files to a toolbox
            without modifying any existing ones
        """
        return self.check_tb_tree() and self.check_tb_files()
    
    def modify_tbox(self):
        if not os.path.exists(self.get_tb_abs_path()) :
            self.logger.error(
                "\ntoolbox %s does not exists\n" % self.get_tb_name() +
                "in path: %s\n" % self.get_tb_abs_path() +
                "\nIt will be created usind 'usr' style"
                )
            self.__tb_style = 'usr'
            self.create_tbox()
        self.read_style()    
        return self.__status
    
    def read_style(self) :
        dirname = self.get_tb_path2mode()
        filename = os.path.join(dirname,self.get_tb_name()+'.hpp')
        if exist(filename) :
            s = read(filename)
            pattern = re.compile("^// This toolbox is of (.*) type")
            for l in s :
                d1 = re.match(pattern,l)
                if d1 :
                    self.__tb_style = d1.groups()
                    return d1
            
        dirname = self.get_tb_abs_path()
        filename = os.path.join(dirname,'py_data.py')
        if exist(filename) : 
            sys.path.insert(0,dirname)
            from py_data import datas
            s = datas['style']
            sys.path.pop(0)
            self.__tb_style = s
            return s
        
        self.logger.warning(
            "\nno file allowing to determine the style of " % self.get_tb_name() +
            "longer exists.\nAssuming an usr toolbox.\n" 
            )
        self.__tb_style = 'usr'
        return 'usr'
              
if __name__ == "__main__":
    from list_utils import show
    Mylogging.set_level('INFO')
    tb = Toolbox("pipo1",style='sys', mode = 'modify')
    print "get_tb_name()      %s   "%tb.get_tb_name()        
    print "get_tb_pathfnt2()  %s   "%tb.get_tb_pathfnt2()    
    print "get_tb_abs_path()  %s   "%tb.get_tb_abs_path()
    print "get_tb_path2mode() %s   "%tb.get_tb_path2mode()   
    print "get_status()       %s   "%tb.get_status()         
    print "get_tb_style ()    %s   "%tb.get_tb_style ()      
    print "get_tb_namespace() %s   "%tb.get_tb_namespace()   
    print "get_tb_mode()      %s   "%tb.get_tb_mode()         
    print "get_tb_status()    %s   "%tb.get_tb_status()
##     print "toolbox tree"
##    show(tb.get_rel_tree())
##    tb.show_tree()
##    t=tb.get_tree()
##    show(t)
##    tb.remove_tree()
##    show(tb.get_tree_lack())
    print tb.check_tbox()
    tb.update_tbox()
    print tb.check_tbox()
 
