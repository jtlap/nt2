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


"""transitionnal units conversion utlity
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
from nt2_update_units                import Nt2_update_scalar_unit
sys.path.pop(0)
sys.path.pop(0)

def modify_scalar_units(tb_name_list=None, fct_list0=None, style=None) :
    if isinstance(tb_name_list,str) : tb_name_list = [tb_name_list]
    if isinstance(fct_list0,str)     : fct_list0 = [fct_list0]
    if tb_name_list is None : tb_name_list = Nt2_base_infos().get_toolbox_list()
    
    for tb_name in tb_name_list :
        if tb_name != 'models' :
            ntbp = Nt2_tb_props(tb_name)
            if style is None or (style == ntbp.get_tb_style()):
                fct_list = ntbp.get_fcts_list() if fct_list0 is None else fct_list0
                for fct in fct_list :
                    nusu = Nt2_update_scalar_unit(tb_name,fct)
                    nusu.modify_unit()#"vas-y")

       
if __name__ == "__main__" :
    modify_scalar_units("ieee")
