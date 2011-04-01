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


"""py_doc skeletton generation
   the result has to be manually edited by the ceator
   to fit properly to correct functors values and test
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
from py_doc_io                       import Py_doc_io 
sys.path.pop(0)
sys.path.pop(0)

Dict_doc_tpl = [
    "{",
    "    'info'    : 'created by create_py_doc',"
    "    'functor' : {       ## intrinsics values related to functor $fct_name$",
    "        'arity'         : '$arity_str$',    ## functor number of parameters",
    "        'ret_arity'     : '$ret_arity_str$',## must be '0' or omitted if not a tuple", 
    "        'types'         : $types_list$,     ## list of types string",
    "        'simd_types'    : $simd_types_list$,     ## list of simd types string",
    "        'rturn'         : $rturn_dict$,     ## dictionary of return types",
    "        'call_types'    : $call_types_list$,## types used in call ['T']*arity if omitted ",
    "        'type_defs'     : $type_def_list$,  ## supplementary typedefs",
    "        'special'       : $special$,        ## special property",
    "        }, ## end of functor",
    "    'unit'    : {       ## informations for creating unit tests",
    "        'global_header' : { ## header of machin.cpp",
    "            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp",
    "            'stamp'       : 'modified by $author$ the $date$', ## modification stamp",
    "            'included'    : $included$,     ## list of supplementary include directives",
    "            'notes'       : $notes$,        ## list of strings that will be included in a",
    "                                            ## global comment",
    "            },",
    "        'specific_values' : $specific_values$,  ## dictionary of parameters and values to be tested",
    "        'ranges'          :  $ranges$,  ## dictionary of ranges for random tests",
    "        'verif_test'      : { ## verification dictionary",
    "            'simd'            : $translations$,   ## dictionary of translations for simd",
    "            'property_call'   : $property_call$,  ## dictionary of calls per types",
    "            'property_value'  : $property_value$, ## dictionary of alternate calls",
    "            'ulp_thresh'      : $ulp_thresh$,     ## validity thresholds(s)",
    "        },  ## end of verif_test", 
    "    },  ## end of unit ",
    "},",
]


##Example
##Dict_doc_tpl = [  ## list of dictionnaries for different arities of the same functor
##{
##        'functor' : {      ## intrinsics values related to sin
##            'arity'      : '1',   ## functor number of parameters
##            'ret_arity'  : '0',            ## must be '0' or omitted or None if not a tuple 
##            'types'      : ['real_', 'unsigned_int_', 'signed_int_'], ## list of types for which a specific test will be generated
##            'rturn'      : { 'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type' }, ## dict of calls return types for each of <types>
##            'call_types' : [  ],         ## list of types for one call [] default to 'T'
##            'type_defs'  : [  ],          ## list of additional typedef needed (for examples for <call_types>,
##        },
##        'unit'    : { ## informations for creating unit tests
##            'global_header' : { ## properties needed to construct header of sin.cpp
##                'first_stamp' : 'created  by jt the 16/12/2010', ## creation stamp
##                'stamp'       : 'modified by $author$ the $date$', ## modification stamp don't modify please (!)
##                'included'    : ["#include <nt2/include/functions/cos.hpp>",
##                                 "#include <nt2/include/functions/sqr.hpp>"], ## list of extra include directives
##                'notes'       : [],                                ## list of strings that will be included in a global comment
##            },
##            'specific_values' : { ## parameters/values pairs to be asserted
##                                  ## one parameter (no commas) is replicated else use comma separated string
##                                  ## a specific ulp for a value can be introduced in the string result after a comma
##                                  ## or in a dictionnary {'result' : '...','ulp_thresh','...'}
##                'real_'       : {
##                    'nt2::Inf<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
##                    'nt2::Minf<T>()':  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
##                    'nt2::Pi<T>()'  :  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0.75'},
##                    'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
##                    'nt2::Pi<T>()/2':  {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
##                    'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()' ,'ulp_thresh':'0'},
##                },
##                'signed_int_   ': {
##                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},
##                },
##                'default': {
##                    'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},
##                },
##            },
##            'verif_test' : { ## assert result of property call equal to property values
##                             ## up to ulp_threshold (0 means strict equality) for random
##                             ## values uniformly distributed in ranges
##                'property_call' : { 'real_' :  ["nt2::sqr(nt2::sin(a0))+nt2::sqr(nt2::cos(a0))",
##                                                  "nt2::sin(nt2::Two<T>()*a0)"]},
##                'property_value' :{ 'real_' :  ['nt2::One<T>()',"nt2::Two<T>()*nt2::sin(a0)*nt2::cos(a0)"], },
##                'ulp_thresh'     :{ 'real_' :  ['0.5','0.5'],},
##                'nb_rand'        :'100',
##                'ranges' : {
##                     'default'       : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
##                     'real_'         : [['-nt2::Pi<T>()','nt2::Pi<T>()']],
##                     'signed_int_'   : [['T(-40)','T(40)']],
##                     'unsigned_int_' : [['T(0)','T(40)']],
##                },
##            },
##        },
##   },     
##]

class Py_doc_base(Py_doc_io) :
    def __init__(self, tb_name, fct_name) :
        Py_doc_io.__init__(self, tb_name, fct_name)
     
    def construct_new_dict_txt(self) :
        res = ["[ ## script modified by create_py_doc.py"]
        for a in self.get_fct_arities() :
            txt = Dict_doc_tpl
            txt = self.replacements(txt, '\$fct_name\$',       self.get_fct_name() )                   
            txt = self.replacements(txt, '\$arity_str\$',      str(a) )                    ## fct number of arguments
            txt = self.replacements(txt, '\$ret_arity_str\$',  self.get_fct_ret_arity()  ) ## must be '0' or omitted if not a tuple          
            txt = self.replacements(txt, '\$types_list\$',     self.get_types_list()     ) ## list of types string                         
            txt = self.replacements(txt, '\$simd_types_list\$',self.get_simd_types_list()     ) ## list of types string                         
            txt = self.replacements(txt, '\$rturn_dict\$',     self.get_rturn_dict()     ) ## ditionary of return types                    
            txt = self.replacements(txt, '\$call_types_list\$',self.get_call_types_list()) ## types used in call ['T']*arrity if omitted   
            txt = self.replacements(txt, '\$type_def_list\$',  self.get_type_def_list()  ) ## supplementary typedefs
            txt = self.replacements(txt, '\$first_stamp\$',    self.get_first_stamp()    ) ## first creation
            txt = self.replacements(txt, '\$stamp\$',          self.get_stamp()          ) ## current stamp
            txt = self.replacements(txt, '\$included\$',       self.get_included()       ) ##
            txt = self.replacements(txt, '\$notes\$',          self.get_notes()          ) ##
            txt = self.replacements(txt, '\$specific_values\$',self.get_specific_values()) ##
            txt = self.replacements(txt, '\$ranges\$',         self.get_ranges(a)        ) ##
            txt = self.replacements(txt, '\$property_call\$',  self.get_property_call(a) ) ##
            txt = self.replacements(txt, '\$property_value\$', self.get_property_value(a)) ##
            txt = self.replacements(txt, '\$ulp_thresh\$',     self.get_ulp_thresh(a)    ) ##
            txt = self.replacements(txt, '\$translations\$',   self.get_translations()   ) ## 
            txt = self.replacements(txt, '\$special\$',        self.get_special()   ) ## 
            res += txt
        res += ["]"]
        return res

    def get_types_list(self)      : return  "['real_', 'unsigned_int_', 'signed_int_']"
    def get_simd_types_list(self) : return  "['realconvert_']"
    def get_rturn_dict(self)      : return "{ 'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type' }"
    def get_call_types_list(self) : return "[]"
    def get_type_def_list(self)   : return "[]"     
    def get_first_stamp(self)     : return 'created  by ' + self.author +' the ' + self.date
    def get_stamp(self)           : return 'modified  by ' + self.author +' the ' + self.date
    def get_included(self)        : return "[]"      
    def get_notes(self)           : return "[]"         
    def get_specific_values(self) : return "[]"
    def get_special(self)        : return "[]"
    def get_ranges(self,a)          : return "[]"       
    def get_property_call(self,arity)   :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        call = "nt2::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'real_' : '%s',}" % call
    def get_property_value(self,arity)  :
        call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
        value = "nt2::libc::%s(%s)"% (self.get_fct_name(),call_param)
        return "{'real_' : '%s',}" % value
    
    def get_ulp_thresh(self,a)      :
        return "{'real_' : ['0.5'],}"    

    def get_translations(self) : return "{}"
    
    def replacements(self, txt, orig, rep) :
        if isinstance(rep,str) :
            return [ re.sub(orig,rep,s) for s in txt]
        elif isinstance(rep,list) :
            rep = '\n'.join(rep)
            txt = '\n'.join([ re.sub(orig,rep,s) for s in txt])
            return txt.split('\n')

if __name__ == "__main__" :
    pass
