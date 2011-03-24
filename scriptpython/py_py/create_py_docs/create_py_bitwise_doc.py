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


"""creation of py docs for bitwise toolbox
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
  

class Mk_doc_skeleton_for_bitwise(create_Py_doc_base) :
    def __init__(self, fct_name) :
        Create_py_doc_base.__init__(self, "bitwise", fct_name)

    def get_specific_values(self) :
        name = self.get_fct_name()
        if re.match("e.*",name)  :
            v = [
                "{",
                "                'real_'       : {",
                "                    'nt2::Inf<T>()'  :  {'result' : 'nt2::Inf<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::Minf<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Nan<T>()'  :  {'result' : 'nt2::Nan<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()'  :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Half<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Mone<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Mhalf<T>()':  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Zero<T>()' :  {'result' : 'nt2::One<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "                'signed_int_   ': {",
                "                    'nt2::Zero<T>()' :  {'result' : 'nt2::One<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()'  :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Mone<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "                'default': {",
                "                    'nt2::Zero<T>()':   {'result' : 'nt2::One<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()' :   {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "           }",
            ]
        elif re.match("l.*$",name) :
            v =[
                "{",
                "                'real_'       : {",
                "                    'nt2::Inf<T>()' :  {'result' : 'nt2::Inf<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::Minf<T>()':  {'result' : 'nt2::Nan<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                    'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::Half<T>()':   {'result' : 'nt2::One<r_t>()',  'ulp_thresh':'0.5'},",
                "                    'nt2::Quarter<T>()':  {'result' : 'nt2::Sqrt_2o_2<r_t>()','ulp_thresh':'0.5'},",
                "                    'nt2::Zero<T>()':  {'result' : 'nt2::Minf<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "                'signed_int_': {",
                "                    'nt2::Zero<T>()':  {'result' : 'nt2::Minf<r_t>()','ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "                'default': {",
                "                    'nt2::Zero<T>()':  {'result' : 'nt2::Minf<r_t>()','ulp_thresh':'0.5'},",
                "                    'nt2::One<T>()' :  {'result' : 'nt2::Zero<r_t>()', 'ulp_thresh':'0.5'},",
                "                },",
                "           }",
                 ]
        else :    
            v = [
                "{",
                "                'real_'       : {",
                "                    'nt2::Inf<T>()' :  {'result' : 'nt2::Inf<r_t>()' ,'ulp_thresh':'0.5'},",
                "                    'nt2::Minf<T>()':  {'result' : 'nt2::Zero<r_t>()' ,'ulp_thresh':'0.5'},",
                "                    'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0.5'},",
                "                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.5'},",
                "                },",
                "                'signed_int_   ': {",
                "                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.5'},",
                "                },",
                "                'default': {",
                "                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.5'},",
                "                },",
                "           }",
                 ]
        return v

    def get_rturn_dict(self)      :
        return "{ 'default' : 'T' }"
    def get_ranges(self,a)          :
        name = self.get_fct_name()
        if re.match("l.*",name)  :
             v = [
                "{",
                "             'default'       : ["+ ','.join(['["T(0)"', '"T(10)"]']*a) +"],",
                "              }",
                 ]
        else :
             v = [
                "{",
                "             'default'       : ["+ ','.join(['["T(-10000)"', '"T(10000)"]']*a) +"],",
                "              }",
                 ]
        return v

    def get_included(self) :
        return "[]"

    def get_ulp_thresh(self,a)      :
        return "{'default' : ['0'],}"    

    def get_types_list(self)      :
        return  "['real_', 'integer_']"

    def get_property_call(self,arity)   :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        call = "nt2::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'integer_' : ['%s'],}" % call
    def get_property_value(self,arity)  :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        value = "nt2::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'integer_' : ['%s'],}" % value

if __name__ == "__main__" :
    ntp = Nt2_tb_props("bitwise")
    fcts = ntp.get_fcts_list()
    fcts = ["ffs"]
    for fct in  fcts :
        print(fct)
        mds = Mk_doc_skeleton_for_bitwise(fct)
        print(mds)
##        mds.write_pydoc()
