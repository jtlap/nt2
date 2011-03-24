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
    "            'no_ulp'      : $no_ulp$,",
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

class Create_py_doc_base(Py_doc_io) :
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
            txt = self.replacements(txt, '\$no_ulp\$',         self.get_no_ulp()   ) ## 
            res += txt
        res += ["]"]
        return res

    def get_types_list(self)      : return  "['real_', 'unsigned_int_', 'signed_int_']"
    def get_no_ulp(self)          : return  "'False'"
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
