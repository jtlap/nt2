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


"""utilities to remove a functor from a toolbox
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

import re
import shutil
from display_utils                   import show
from files_utils                     import write, exist, read
from nt2_base_struct                 import Nt2_base_struct
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from pprint                          import PrettyPrinter
from unit_base_gen                   import Base_gen
from unit_global_header_gen          import Global_header_gen
from unit_type_header_gen            import Type_header_test_gen
from unit_specific_values_gen        import Specific_values_test_gen
from unit_random_verif_gen           import Random_verif_test_gen
from nt2_tb_struct                   import Nt2_tb_struct
from nt2_archis_struct               import Nt2_archis_struct
from headerfiles                     import Headers

sys.path.pop(0)
sys.path.pop(0)
sys.path.pop(0)



class Remove_functor_skel(Base_gen,Nt2_tb_struct) :
    def __init__(self,tb_name,fct_name) :
        Base_gen.__init__(self, tb_name, fct_name, 'scalar')
        Nt2_tb_struct.__init__(self)
        self.tb_files  = self.get_rel_tb_unique_files(tb_name)
        self.fct_files = self.get_rel_tb_fcts_files(tb_name,fct_name)
        self.unique_files = self.get_rel_tb_unique_files(tb_name)

    def remove_files(self) :
        for f in self.fct_files :
            p = os.path.join(self.get_tb_path(),f)
            if exist(p) and p[-2:]!='py' : self.delete(p)
        for f in self.unique_files :
            p = os.path.join(self.get_tb_path(),f)
            if exist(p) :
                [ignore, fname] = os.path.split(p)
##            print(fname)
##            print("%s exists is %s"%(p,exist(p)))
                if fname == 'CMakeLists.txt' :
                    self.suppresslinein(p,self.get_fct_name()+'.cpp')
                elif fname ==  self.get_tb_name()+'.hpp':
                    self.suppresslinein(p,self.get_fct_name()+'.hpp')
                else :
                    print(fname)

    def delete(self,p) :
        print("deleting %s"%p)
        os.remove(p)

    def suppresslinein(self,p,token) :
        txt = read(p);
        txt = [re.sub('\s*'+token,'',t) for t in txt ]
        write(p,txt,check=False)



if __name__ == "__main__" :
    tb_name = "euler"
    fcts = ["gamma_0_1"]
    for fct_name in fcts :
        print fct_name
        afs = Remove_functor_skel(tb_name,fct_name)
        afs.remove_files()


