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


"""boost_math specific
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
import re
import shutil
from files_utils            import read, exist, write
from nt2_toolbox_infos      import Toolbox_infos
from nt2_fundamentals       import Nt2_base_infos
from nt2_tb_functors_infos  import Fctor_infos
from display_utils          import show
from mk_new_functor         import Mk_fctor       
tb_targets =[
    "gsl_specfun",
]
class Boost_math_fct(Fctor_infos) :
    def __init__(self, tb_name, fct_name, mode, submode="") :
        Fctor_infos.__init__(self, tb_name, fct_name, mode, submode="") 
        self.__old_def_txt = self.__read_old_def_txt()
        
    def get_old_def_txt(self)   : return self.__old_def_txt

    def get_def_header(self) :
        s = self.get_old_def_txt()
        for i,l in enumerate(s) :
            if re.match("namespace nt2.*",l) : return s[:i+2]
        return [""]


    def __read_old_def_txt(self) :
        p = os.path.join(tbi.get_def_path(),fct+'.hpp')
        r = read(p)
        return r
    def __read_old_unit_txt(self) :
        p = os.path.join(tbi.get_unit_path(),"scalar",fct+'.cpp')
        r = read(p)
        return r
    
    def __write_def_txt(self,s) :
        p = os.path.join(tbi.get_def_path(),fct+'.hpp')
        shutil.move(p,re.sub('.hpp','.bak',p))
        write(p,s,False)

    def change_units(self) :
        p = os.path.join(tbi.get_unit_path(),"scalar",fct+'.cpp')
#        shutil.move(p,re.sub('.cpp','.bak',p))
        s = read(p)
#        show(s[:-2])
        write(p,s[:-2],False)
    
##    def change_def_header(self)  :
##        s = self.get_old_def_txt()
##        point = 0
##        for i,l in enumerate(s) :
##            if re.match("#include <nt2/toolbox/boost_math/include.hpp>",l) :
##               s[i] = "#include <nt2/toolbox/boost_math/"+self.get_fct_name()+".hpp>"
##            if re.match("#include <nt2/toolbox/boost_math/"+self.get_fct_name()+".hpp>",l) :
##               s[i] = "#include <boost_math/"+self.get_fct_name()+".hpp>"
##            if re.match("#include <boost_math/"+self.get_fct_name()+".hpp>",l) :
##               s[i] = "#include <boost/math/special_functions/"+self.get_fct_name()+".hpp>"
              
##            if re.match(" *NT2_FUNCTION_IMPLEMENTATION\(",l) :
##                if re.match(" *}",s[i-1]) :
##                    t = s[i-1]
##                    s[i-1] = "  "+s[i]
##                    s[i] = t
##                    break
##        self.__write_def_txt(s)         
##        return s
         
    

for tb in tb_targets :
    tbi = Toolbox_infos(tb)
    isa = 'scalar'
    if tbi.get_tb_style() =='usr' :
        print tb
        for fct in tbi.get_fctors_list() :
            bf = Boost_math_fct(tb,fct,isa)
            bf.change_units()
            



