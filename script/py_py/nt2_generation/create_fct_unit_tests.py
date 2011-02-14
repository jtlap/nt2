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


"""unit test generation for a functor
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

import re
import shutil
from display_utils                   import show
from files_utils                     import write, exist
from nt2_base_struct                 import Nt2_base_struct
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from pprint                          import PrettyPrinter
from unit_base_gen                   import Base_gen
from unit_global_header_gen          import Global_header_gen
from unit_type_header_gen            import Type_header_test_gen 
from unit_specific_values_gen        import Specific_values_test_gen 
##from unit_random_gen                 import Random_test_gen
##from unit_tuple_random_gen           import Random_tuple_test_gen  
from unit_random_verif_gen           import Random_verif_test_gen
sys.path.pop(0)
sys.path.pop(0)

def create_unit(tb_name,fct_name,mode) :
    bg = Base_gen(tb_name,fct_name,mode)
    ghg = Global_header_gen(bg)
    r = ghg.get_gen_result()
    dl = bg.get_fct_dict_list()
    for d in dl :
        types = bg.recover("types",d["functor"],[])
        d_unit = d["unit"]
        for typ in types :
            thg = Type_header_test_gen(bg,d,typ)
            r+=thg.get_gen_beg()
            if d_unit.get("specific_values",None) :
                print("specific")
                svt = Specific_values_test_gen(bg,d,typ)
                r += svt. get_gen_result()
            if d_unit.get("verif_test",None) :
                print("verif")
                vtg = Random_verif_test_gen(bg,d,typ)
                r += vtg. get_gen_result()
            r+=thg.get_gen_end()
    return r

def write_unit(tb_name,fct_name,mode,s,check=False) :
    nfp = Nt2_fct_props(tb_name,fct_name,mode)
    p = nfp.get_fct_unit_path(mode)
    print "write to %s"%p
    show(s)
    write(p,s,check)

    
if __name__ == "__main__" :
    tb_name = "trigonometric"
    fcts = Nt2_tb_props(tb_name).get_fcts_list()
    fcts = ["sin"]
    for fct in fcts :
        print fct
        r= create_unit(tb_name,fct,'scalar')
        write_unit(tb_name,fct,'scalar',r)
    
