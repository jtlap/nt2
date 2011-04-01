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
  

class Mk_doc_skeleton_for_fuzzy(Create_py_doc_base) :
    def __init__(self, fct_name) :
        Create_py_doc_base.__init__(self, "fuzzy", fct_name)

    def get_included(self)        : return "['#include <nt2/sdk/meta/logical.hpp>']"      
    def get_specific_values(self) :
        return [
                "{",
                "                'default'       : {",
                "                    '0,0,1' :  {'result' : 'nt2::True<r_t>()',  'ulp_thresh':'0'},",
                "                    '0,1,1':  {'result' : 'nt2::False<r_t>()',  'ulp_thresh':'0'},",
                "                },",
                "                'real_'       : {",
                "                    '0,0,1' :  {'result' : 'nt2::True<r_t>()',  'ulp_thresh':'0'},",
                "                    '0,1,1':  {'result' : 'nt2::False<r_t>()',  'ulp_thresh':'0'},",
                "                },",
                "           }",
                 ]
 

    def get_simd_types_list(self) :
        return  "['real_','signed_int_','unsigned_int_']"
    def get_rturn_dict(self)      :
        return "{ 'default' : 'typename nt2::meta::logical<T>::type' }"
    def get_ranges(self,a) :
        v = [
            "{",
            "             'default'       : ["+ ','.join(['["T(-10)"', '"T(10)"]']*a) +"],",
            "              }",
            ]
        return v

    def get_ulp_thresh(self,a)      :
        return "{'default' : ['0'],}"    
    def get_special(self)      :
        return "['fuzzy',]"    

    def get_types_list(self)      :
        return  "['real_', 'signed_int_','unsigned_int_']"

    def get_property_call(self,arity)   :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        name = self.get_fct_name()
        call = "nt2::%s(%s)"% (name,call_param)
        return "{'default' : ['%s'],}" % call

    def get_property_value(self,arity)  :
        name = self.get_fct_name()
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        value = "nt2::%s(%s)"% (name,call_param)
        return "{'default' : ['%s'],}" % value

    def get_no_ulp(self)          : return  "True"

if __name__ == "__main__" :
    ntp = Nt2_tb_props("fuzzy")
    fcts = ntp.get_fcts_list()
##    fcts = ["almost_equal"]
    for fct in  fcts :
        print(fct)
        mds = Mk_doc_skeleton_for_fuzzy(fct)
##//        print(mds)
        res =mds.construct_new_dict_txt()
        PrettyPrinter().pprint(res)
        p = os.path.join(mds.get_doc_path(),mds.get_fct_name()+'.py')
        write(p,res,check=False,verbose=True)
##       mds.write_pydoc()
