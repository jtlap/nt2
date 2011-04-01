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


"""transitionnal doc conversion utlity
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
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_fct_internals               import Nt2_fct_internals
from nt2_update_def                  import Nt2_update_def
sys.path.pop(0)
sys.path.pop(0)

def modify_defs(tb_name_list, fct_list=None, style=None) :
    if isinstance(tb_name_list,str) : tb_name_list = [tb_name_list]
    if isinstance(fct_list,str)     : fct_list = [fct_list]
    if tb_name_list is None : tb_name_list = self.get_toolbox_list()
    for tb_name in tb_name_list :
        ntbp = Nt2_tb_props(tb_name)
        if style is None or (style == ntbp.get_tb_style()):
            if fct_list is None : fct_list =ntbp.get_fcts_list()
            for fct in fct_list :
                nud = Nt2_update_def(tb_name,fct)
                nud.modify_def()

       
if __name__ == "__main__" :
    modify_defs("arithmetic")
