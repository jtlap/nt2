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


"""transitionnal fcts conversion utlity
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
import datetime
import shutil
import re
from files_utils                     import write, exist, read
from nt2_base_infos                  import Nt2_base_infos
from pprint                          import PrettyPrinter
from nt2_base_infos                  import Nt2_base_infos
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_fct_internals               import Nt2_fct_internals
from nt2_update_funcs                import Nt2_update_scalar_fct
sys.path.pop(0)
sys.path.pop(0)

def run_benches(tb_name_list=None, fct_list0=None, modes='all') :
    if modes == 'all' : modes = ['scalar','simd']
    if isinstance(modes,str) : modes = [modes]
    if isinstance(tb_name_list,str) : tb_name_list = [tb_name_list]
    if isinstance(fct_list0,str)     : fct_list0 = [fct_list0]
    if tb_name_list is None : tb_name_list = Nt2_base_infos().get_toolbox_list()
    
    for tb_name in tb_name_list :
        if tb_name != 'models' :
            ntbp = Nt2_tb_props(tb_name)
                fct_list = ntbp.get_fcts_list() if fct_list0 is None else fct_list0
                for fct in fct_list :
                    for mode in modes :
                    nusf = Nt2_bench_fct(tb_name,fct)
                    nusf.execute_bench()

       
if __name__ == "__main__" :
    modify_fcts("libc",style="usr")
