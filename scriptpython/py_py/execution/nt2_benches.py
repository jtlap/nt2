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

"""update of units syntax : transitionnal
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
import string
from commands        import getoutput
from files_utils                     import write, exist, read
from nt2_base_infos                  import Nt2_base_infos
from pprint                          import PrettyPrinter
from nt2_tb_props                    import Nt2_tb_props

sys.path.pop(0)
sys.path.pop(0)


class Nt2_benches(Nt2_tb_props) :
    def __init__(self, tb_name) :
        Nt2_tb_props.__init__(self,tb_name)

        
    def get_path(self,fct,mode) :
        return os.path.join( self.get_tb_path(),'bench',mode,fct+".cpp")

    def get_exec_name(self,fct,mode) :
        n = fct+'.'+self.get_tb_name()+'.'+mode+'.bench'
        return os.path.join( self.get_tb_path(),'bench',mode,n)


    def show(self,fct,mode) :
       txt =  read(self.get_path(fct,mode))
       print("===============")
       PrettyPrinter().pprint(txt)
       print("===============")

    def execute(self,fct,mode) :
        print(self.get_exec_name(fct,mode))
        r=getoutput(self.get_exec_name(fct,mode))
        PrettyPrinter().pprint(r.split('\n'))
        
if __name__ == "__main__" :
    nud = Nt2_benches("arithmetic")
    nud.show("abs","scalar")
    nud.execute("abs","scalar")
