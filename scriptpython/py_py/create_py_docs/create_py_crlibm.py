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
from create_py_doc_base              import Create_py_doc_base

sys.path.pop(0)
sys.path.pop(0)
  

class Mk_doc_skeleton_for_crlibm(Create_py_doc_base) :
    def __init__(self, fct_name) :
        Create_py_doc_base.__init__(self, "crlibm", fct_name)

    def get_specific_values(self) :
        return "{}"
 

    def get_simd_types_list(self) :
        return  "[]"
    def get_rturn_dict(self)      :
        return "{ 'default' : 'T' }"
    def get_ranges(self,a)          :
        v = [
            "{",
            "             'default'       : ["+ ','.join(['["T(-100)"', '"T(100)"]']*a) +"],",
            "              }",
            ]
        return v

    def get_included(self) :
        name = self.get_fct_name()
        n = name[:-3] if ( name[-3:] in ['_rd','_rn','_ru','_rz']) else name
        return "['#include <nt2/include/functions/%s.hpp>']"%n

    def get_ulp_thresh(self,a)      :
        return "{'default' : ['1'],}"    
    def get_special(self)      :
        return "['crlibm',]"    

    def get_types_list(self)      :
        return  "['real_']"

    def get_property_call(self,arity)   :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        name = self.get_fct_name()
        suf = "" if ( name[-3:] in ['_rd','_rn','_ru','_rz']) else "<rn>"
        call = "nt2::crlibm::%s%s(%s)"% (self.get_fct_name(),suf,call_param)
        return "{'default' : ['%s'],}" % call
    def get_property_value(self,arity)  :
        name = self.get_fct_name()
        n = name[:-3] if ( name[-3:] in ['_rd','_rn','_ru','_rz']) else name
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        value = "nt2::%s(%s)"% (n,call_param)
        return "{'default' : ['%s'],}" % value

if __name__ == "__main__" :
    ntp = Nt2_tb_props("crlibm")
    fcts = ntp.get_fcts_list()
 ##   fcts = ["acos"]
    for fct in  fcts :
        print(fct)
        mds = Mk_doc_skeleton_for_crlibm(fct)
##//        print(mds)
        res =mds.construct_new_dict_txt()
        PrettyPrinter().pprint(res)
        p = os.path.join(mds.get_doc_path(),mds.get_fct_name()+'.py')
        write(p,res,check=False,verbose=True)
##       mds.write_pydoc()
