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
from py_doc_base                     import Py_doc_base
from create_py_doc_base              import Create_py_doc_base

sys.path.pop(0)
sys.path.pop(0)
  

class Mk_doc_skeleton_for_elliptic(Create_py_doc_base) :
    def __init__(self, fct_name) :
        Create_py_doc_base.__init__(self, "elliptic", fct_name)
        
    def get_specific_values(self) :
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
        return v

    def get_ranges(self,a)          :
        v = [
            "{",
            "             'default'       : ["+ ','.join(['["T(-10)"', '"T(10)"]']*a) +"],",
            "              }",
            ]
        return v

    def get_included(self) :
        trig_const ='#include <nt2/toolbox/exponential/include/constants.hpp>'
        boost_math = '#include <nt2/toolbox/boost_math/include/%s.hpp>' % self.get_fct_name()
        cephesl    = 'extern "C" {long double %s(long double);}'%self.get_fct_name()
        return "['"+trig_const+"','"+boost_math+"','"+cephesl+"']"
##        return [trig_const,cephes]

    def get_property_call(self,arity)   :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        call = "nt2::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'real_' : ['%s'],}" % call
    def get_property_value(self,arity)  :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        value = "nt2::boost_math::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'real_' : ['%s'],}" % value

##    def get_dict_list(self) : return self.d

if __name__ == "__main__" :
    ntp = Nt2_tb_props("elliptic")
    fcts = ntp.get_fcts_list()
    fcts = ["ellie"]
    for fct in fcts :
        print(fct)
        mds = Mk_doc_skeleton_for_elliptic(fct)
##        print(mds)
        mds.write_pydoc(force=True)

