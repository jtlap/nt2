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


"""utilities to add a module to a toolbox
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"bench_generation"))
from unit_creation     import create_unit
from bench_creation     import create_bench

import re
import shutil
from display_utils                   import show
from files_utils                     import write, exist, read, mkdir
from nt2_base_infos                  import Nt2_base_infos
from nt2_modules                     import Nt2_modules
##from nt2_tb_props                    import Nt2_tb_props
##from nt2_fct_props                   import Nt2_fct_props
##from pprint                          import PrettyPrinter
##from unit_base_gen                   import Base_gen
##from unit_global_header_gen          import Global_header_gen
##from unit_type_header_gen            import Type_header_test_gen
##from unit_specific_values_gen        import Specific_values_test_gen
##from unit_random_verif_gen           import Random_verif_test_gen
from nt2_tb_struct                   import Nt2_tb_struct
from nt2_archis_struct               import Nt2_archis_struct
##from headerfiles                     import Headers

sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)

cmakelist1 = """
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add global $part$ driver rules
################################################################################
ADD_CUSTOM_TARGET($tb_name$.scalar.$part$)
ADD_CUSTOM_TARGET($tb_name$.simd.$part$)
ADD_DEPENDENCIES($tb_name$.$part$ $tb_name$.scalar.$part$ $tb_name$.simd.$part$)

##############################################################################
# Toolbox $tb_name$ $part$ tests
##############################################################################
nt2_module_use_modules($part$ predicates)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)

"""
cmakelist2 = """
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
# List of $simdornot$ test files for toolbox $tb_name$
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE '.cpp' '' EXAMPLE ${EXAMPLE})
  nt2_module_add_$part$($tb_name$.$simdornot$.${EXAMPLE}.$part$ ${EXAMPLE}.cpp)
ENDFOREACH()

"""

cmakelist3 = """
##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

cmake_minimum_required(VERSION 2.6)
include(NT2Module)
nt2_module_main($tb_name$)

"""

pydata = """
datas = {
'style' : '$style$'
}
"""

tbmain1 = """
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_$Tb_name$_HPP_INCLUDED
#define NT2_TOOLBOX_$Tb_name$_HPP_INCLUDED

// Please do not remove or modify the next line comment
// This toolbox is of $style$ type
#include <nt2/nt2.hpp>
#include <nt2/toolbox/$tb_name$/$tb_name$.hpp>

#endif

"""

tbmain2 = """
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_$Tb_name$_$Tb_name$_HPP_INCLUDED
#define NT2_TOOLBOX_$Tb_name$_$Tb_name$_HPP_INCLUDED

//<include> please don't modify between these tags
//<\include>

#endif

"""

include = """
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_$Tb_name$_INCLUDE_HPP_INCLUDED
#define NT2_TOOLBOX_$Tb_name$_INCLUDE_HPP_INCLUDED
#include <nt2/sdk/simd/preprocessor/include.hpp>

#define NT2_$Tb_name$_BASE() nt2/toolbox/$tb_name$/function/scalar/
#define NT2_$Tb_name$_RELATIVE() nt2/toolbox/$tb_name$/function/

#define NT2_$Tb_name$_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_$Tb_name$_RELATIVE, F)

#endif

"""


d = { "bench/CMakeLists.txt" :
      {
          "text" : cmakelist1,
          "token" : ["part","tb_name"]
        },
      "bench/scalar/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "bench/simd/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "unit/CMakeLists.txt" :
      {
          "text" : cmakelist1,
          "token" : ["part","tb_name"]
        },
      "unit/scalar/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "unit/simd/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "cover/CMakeLists.txt" :
      {
          "text" : cmakelist1,
          "token" : ["part","tb_name"]
        },
      "cover/scalar/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "cover/simd/CMakeLists.txt" :
      {
          "text" : cmakelist2,
          "token" : ["part","tb_name","simdornot"]
        },
      "./py_data.py" :
      {
          "text" : pydata,
          "token" : ["style"]
        },
      "./CMakeLists.txt" :
      {
          "text" : cmakelist3,
          "token" : ["tb_name"]
        },
      "include/nt2/toolbox/$tb_name$/$tb_name$.hpp" :
      {
          "text" : tbmain2,
          "token" : ["Tb_name","tb_name","style"]
        },
      "include/nt2/toolbox/$tb_name$.hpp" :
      {
          "text" : tbmain1,
          "token" : ["Tb_name","tb_name","style"]
        },
      "include/nt2/toolbox/$tb_name$/include.hpp" :
      {
          "text" : include,
          "token" : ["Tb_name","tb_name"]
        },
     }

def dollarize(t) :
   return "\$"+t+"\$"


class Add_module_skel(Nt2_base_infos,Nt2_tb_struct) :
    def __init__(self,tb_name,style='sys') :
        Nt2_base_infos.__init__(self)
        Nt2_tb_struct.__init__(self)
        self.tb_name = tb_name
        self.style = style
        self.primary_abs_tb_path = os.path.join(self.get_toolboxes_path(),tb_name)
        self.secundary_abs_tb_path = os.path.join(self.primary_abs_tb_path,'include','nt2','toolbox',tb_name)
        self.part = ""

    def value(self,t,f) :
        dico = {
            "part"    : self.part,
            "tb_name" : self.tb_name,
            "Tb_name" : self.tb_name.upper(),
            "simdornot" : "simd" if ("simd" in f) else "scalar",
            "style"   : self.style,
            }
        return dico[t]


    def create_dirs(self) :
        def cond_mkdir(p) :
            if not exist(p) :
                mkdir(p)
                print(p)

        p = self.primary_abs_tb_path
        for rep in Nt2_tb_struct.Required_directories :
            cond_mkdir(os.path.join(p,rep))
        for rep in Nt2_tb_struct.Required_tree.keys() :
            if rep == "function" :
                pass
            elif rep != '.' :
                there = os.path.join(p,rep)
                for r in Nt2_tb_struct.Required_tree[rep] :
                    here = os.path.join(there,r)
                    cond_mkdir(here)
        here = os.path.join(p,'include','nt2')
        cond_mkdir(here)
        here = os.path.join(here,'toolbox')
        cond_mkdir(here)
        here = os.path.join(here,tb_name)
        cond_mkdir(here)
        here = os.path.join(here,'function')
        cond_mkdir(here)
        there = os.path.join(here,'scalar')
        cond_mkdir(there)
        there = os.path.join(here,'simd')
        cond_mkdir(there)
        for archi in Nt2_archis_struct.Archs.keys() :
            v = Nt2_archis_struct.Archs[archi]
            for va in v.Variants.keys() :
                here1 = os.path.join(here,v.Variants[va][0])
                cond_mkdir(here1)
                if len(v.Variants[va]) > 1 :
                   here1 = os.path.join(here1,v.Variants[va][1])
                   cond_mkdir(here1)

    def create_dir_files(self) :
        l =self.get_rel_tb_unique_files(self.tb_name)
        keys = [re.sub("\$tb_name\$",self.tb_name,k) for k in d.keys()]

        for f in l :
            fsplit = f.split('/')
            self.part = fsplit[0]
            if f in keys :
                kf = f
                if self.tb_name in f :
                    kf = re.sub(tb_name,"$tb_name$",kf)
                p =  os.path.normpath(os.path.join(self.primary_abs_tb_path, f))
                self.wr_txt(d,kf,p)
##            print(f)
##            print(os.path.join(self.primary_abs_tb_path, f))
##            print(exist(os.path.normpath(os.path.join(self.primary_abs_tb_path, f))))

    def wr_txt(self,dico,key,p) :
        txt =  d[key]["text"]
        for t in d[key]["token"] :
            txt = re.sub(dollarize(t),self.value(t,key),txt)
        txt = re.sub("'",'"',txt)
        print(p)
        print(txt)
        write(p,txt,True)

if __name__ == "__main__" :
##    mds = Nt2_modules()
##    for tb_name in mds.get_modules_list() :
   tb_name = "arithmetic"
   ams = Add_module_skel(tb_name,'sys')
   ams.create_dirs()
   ams.create_dir_files()

