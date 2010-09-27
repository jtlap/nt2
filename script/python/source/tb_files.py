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

"""Tools for playing with nt2 toolboxes tree structure
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

from file_utils    import write, exist, mkdir, read
from headerfiles   import Headers
from nt2_base      import Nt2
from mylogging     import Mylogging
from tb_tree       import Tb_tree 

class Tb_files(Tb_tree) :
    """ creation and deletion of unique files in toolbox trees.
    <root_name>     is the name of the root directory
    <root_abs_path> is the path to the root directory
                    not including it
    <rel_tree>      is the list of path from the root (not
                    including it to be created or deleted)

    
    """
    def __init__(self, root_name, root_abs_path, rel_tree, files, style='usr') :
        self.logger = Mylogging("nt2.tb_files.Tb_files")
        self.__tb_style = style
        self.__tb_files = files
        self.__root_abs_path = root_abs_path
        Tb_tree.__init__(self,root_name, root_abs_path, rel_tree)

    def get_tb_files(self) : return self.__tb_files

    def __mk_tb_files(self,check=False) :
        """ calling this method suppose that create_tree
        was invoked earlier
        """
        n = self.get_root_name()+'/'
        for a,r in  zip(self.get_abs_tree(),self.get_rel_tree()) :
            if not exist(a) :
               self.logger.info("\ncreating : \n%s" % a)
               mkdir(a)
            key = string.replace(r,n,"",1)
            if key in self.get_tb_files() :
                for action_name, name in self.get_tb_files()[key].items() :
                    if name == "$root_name$" : name = self.get_root_name()
                    action = getattr(Tb_files,"mk_"+action_name,None)
                    if callable(action) : 
                        value = action(self,check,a,r,name,key)
                        if (check == "check_only") and not value : return False
#NO UPDATE#        if self.__tb_style == 'sys' : self.update_CMake(check)
        return True
    
    def create_tb_files(self) :
        self.__mk_tb_files(check=False)
      
    def update_tb_files(self) :
        self.__mk_tb_files(check=True)

    def check_tb_files(self) :
        return self.__mk_tb_files(check='check_only')

    def update_CMake(self,check) :
        lp = self.__root_abs_path.split('/')
        p = os.path.join('/'.join(lp[:-4]),'CMakeLists.txt')
        s= read(p)
        pattern = "ADD_SUBDIRECTORY\(\${PROJECT_BINARY_DIR}/include/nt2/toolbox/"+self.get_tb_name()+'\)'
        for l in s :
            m = re.match(pattern, l)
            if m : return
        s.append(string.replace(pattern,'\\',''))    
        write(p,s,False)

    def mk_root(self,check,a,r,name,key) :
        """the created file will contain the include list of functors
        immediately available from the toolbox.
        """
        fname = os.path.join(a,name+'.hpp')
        if check == 'check_only' :
            r = exist(fname)
            if not r : self.logger.info("\nroot file %s does not exist" % fname)
            return r
        self.logger.info(
            "\ncreating include template for %s\n" % self.get_root_name()
            )
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp,self.get_root_name())
        h.write_header2(fname,check=check)
        return True

    def mk_py_data(self,check,a,r,name,key) :
        """this file contains python infos for pursuing the toolbox
           completion with functors
        """
        fname = os.path.join(a,name)
        if check == 'check_only' :
            r = exist(fname)
            if not r : self.logger.info("\npy_data file %s does not exist" % fname)
            return r 
        self.logger.info(
            "\ncreating toolbox py datas for %s\n" % self.get_root_name()
            )
        inner_text = [
            "datas = {",
            "'style' : '%s'" % self.__tb_style,
            "}"
            ]
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp, self.get_root_name(),inner=inner_text, ext='.py')
        h.write_header2(fname,flag='inner',check=check)
        return True
        
    def mk_root_include(self,check,a,r,name,key) :
        """the created file  include.hpp contains the BASE_<tb>... MACROS
        under toolbox/<tb>.
        """
        fname = os.path.join(a,'include.hpp')
        if check == 'check_only' : 
            r = exist(fname)
            if not r : self.logger.info("\nroot include file %s does not exist" % fname)
            return r
        self.logger.info(
            "\ncreating toolbox include template for %s\n" % self.get_root_name()
            )
        inner_text = [
            "#include <nt2/sdk/details/preprocessor.hpp>",
            "",
            "#define NT2_$tb_nameupper$_BASE() nt2/toolbox/$tb_name$/function/scalar/",
            "#define NT2_$tb_nameupper$_RELATIVE() nt2/toolbox/$tb_name$/function/",
            "",
            "#if defined(NT2_SIMD_DETECTED)",
            "#define NT2_$tb_nameupper$_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_$tb_nameupper$_RELATIVE, F)",
            "#else",
            "#define NT2_$tb_nameupper$_INCLUDE(F) NT2_PP_INCLUDE(NT2_$tb_nameupper$_BASE, F)",
            "#endif",
            ""
            ]
        inn=[]
        for l in inner_text :
            z=re.sub('\$tb_nameupper\$',self.get_root_name().upper(),l)
            z=re.sub('\$tb_name\$',self.get_root_name(),z)
            inn.append(z)
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp,"include",inner=inn)
        h.write_header2(fname,check=check)

        # phase 2 creation of the CMakeLists global file

        fname = os.path.join(a,'CMakeLists.txt')
        inner_text = [
            "",
            "ADD_SUBDIRECTORY(bench)",
            "ADD_SUBDIRECTORY(unit)",
            "",
            "##############################################################################",
            "## TODO: Write command for building your own sources",
            "##############################################################################"
            ]
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp, "/%s/CMakelists"%key,inner=inner_text, ext='.txt',comment='##')
        h.write_header2(fname,flag='banner+inner',check=check)
        return True

    def mk_base(self,check,a,r,name,key) :
        """the created file is the main include file for the toolboxes users.
        """
        na = os.path.abspath(os.path.join(a,'..'))
        fname = os.path.join(na,name+'.hpp')
        if check == 'check_only' : 
            r = exist(fname)
            if not r : self.logger.info("\nbase file %s does not exist" % fname)
            return r
        self.logger.info(
            "\ncreating toolbox include template for %s\n" % self.get_root_name()
            )
        inner_text = [
            "",
            "// Please do not remove or modify the next line comment",
            "// This toolbox is of %s type" % self.__tb_style,
            "#include <nt2/nt2.hpp>",
            "#include <nt2/toolbox/" + self.get_root_name() + "/"+ \
             self.get_root_name() + ".hpp>",
            ""
            ]
        n = self.get_root_name()+'/'
        rp = 'nt2/toolbox/'
        h = Headers(rp,self.get_root_name(),inner=inner_text)
        h.write_header2(os.path.join(na,name+'.hpp'),check=check)
        return True
        
    def mk_inner(self,check,a,r,name,key) :
        """ creation de CMakeLists.txt dans nt2/<tb>/doc/<name>"""
        fname = os.path.join(a,name)
        if check == 'check_only' : 
            r = exist(fname)
            if not r : self.logger.info("\ninner file %s does not exist" % fname)
            return r
        self.logger.info(
            "\ncreating CMakeLists.txt for %s benches/unit tests\n" % self.get_root_name()
            )
        inner_text = [
            "",
            "################################################################################",
            "# Add global unit driver rules",
            "################################################################################",
            "ADD_CUSTOM_TARGET(%s.scalar.unit)" % self.get_root_name(),
            "ADD_CUSTOM_TARGET(%s.simd.unit)"% self.get_root_name(),
            "ADD_CUSTOM_TARGET(%s.unit)"% self.get_root_name(),
            "",
            "##****************************************************************************",
            "##*     Toolbox %s %s tests" % (self.get_root_name(),key),
            "##****************************************************************************",
            "",
            "ADD_SUBDIRECTORY(scalar)",
            "ADD_SUBDIRECTORY(simd)",
            "",
            "################################################################################",
            "# Add driver rule dependencies",
            "################################################################################",
            "ADD_DEPENDENCIES(%s.unit %s.scalar.unit)" % (self.get_root_name(),self.get_root_name()),  
            "ADD_DEPENDENCIES(%s.unit %s.simd.unit)"% (self.get_root_name(),self.get_root_name()),
            "ADD_DEPENDENCIES(unit %s.unit)"% self.get_root_name(),
            ]
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp,"/%s/CMakelists"%key, inner=inner_text, ext='.txt',comment='##')
        h.write_header2(fname,flag='banner+inner',check=check)
        return True

    def mk_scalar(self,check,a,r,name,key) :
        return self.__mk_s(check,a,r,name,key,"scalar")
        
    def mk_simd(self,check,a,r,name,key) :
        return self.__mk_s(check,a,r,name,key,"simd")
        
    def __mk_s(self,check,a,r,name,key,st) :
        """ creation de CMakeLists.txt dans nt2/<tb>/<unit/bench>/<name>"""
        fname = os.path.join(a,name)
        benchortest = key.split('/')[0] 
        if check == 'check_only' : 
            r = exist(fname)
            if not r : self.logger.info("\ns file %s does not exist" % fname)
            return r
        self.logger.info(
            "\ncreating CMakeLists.txt for %s benchmarks\n" % self.get_root_name()
            )
        inner_text = [
            "",
            "SET( SOURCES",
            "# List of %s test files for toolbox %s"% (st,self.get_root_name()),
            "   )",
            "",
            "##****************************************************************************",
            "# For each filename",
            "##****************************************************************************",
            "FOREACH( EXAMPLE ${SOURCES})",
            "  ##**************************************************************************",
            "  ## Build the executable filename from the example source filename",
            "  ##**************************************************************************",
            '  STRING(REGEX REPLACE ".cpp" ".%s.%s.%s" EXECUTABLE "${EXAMPLE}")'%(self.get_root_name(),st,benchortest),
            '  STRING(REGEX REPLACE ".cpp" "-%s.%s.%s" TEST "${EXAMPLE}")'%(self.get_root_name(),st,benchortest),
            "",
            "  ##**************************************************************************",
            "  ## Add as a target",
            "  ##**************************************************************************",
            "  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})",
            "  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)",
            "  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${NT2_CXX_SIMD_FLAGS})" if st=="simd" else "",         
            "  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})",
            "ENDFOREACH()",
            ]
        rp = os.path.join('nt2/toolbox/',r)
        h = Headers(rp,"/%s/CMakelists"%key, inner=inner_text, ext='.txt',comment='##')
        h.write_header2(os.path.join(a,name),flag='banner+inner',check=check)
        return True
    
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
        "bench",
        "bench/scalar",
        "bench/simd",
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
    some_files =                 {
        "" : {
            "py_data"      : "py_data.py", 
            "base"         : "$root_name$",  
            "root"         : "$root_name$",
            "root_include" : "include.hpp",
            },
        "bench" :            {
            "inner"        : "CMakeLists.txt"
            },
        "bench/scalar" : {
            "scalar"       : "CMakeLists.txt"
            },
        "bench/simd" :   {  
            "simd"         : "CMakeLists.txt",
            },
        "unit" :                 {
            "inner"        : "CMakeLists.txt"
            },
        "unit/scalar" :      {
            "scalar"       : "CMakeLists.txt"
            },
        "unit/simd" :        {  
            "simd"         : "CMakeLists.txt",
            },
         }
    from list_utils import show
    Mylogging.set_level('ALWAYS')
    name = "pipo"
    path = "/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox"
    tb = Tb_files(name,path,a_tree,some_files)
    print "get_root_name()      %s   "%tb.get_root_name()        
    print "get_rel_tree()       %s   "%tb.get_rel_tree()    
    print "get_root_abs_path()  %s   "%tb.get_root_abs_path()             
    tb.show_tree()
    tb.create_tb_files()
##    tb.remove_tree()
##    show(tb.get_tree_lack())

