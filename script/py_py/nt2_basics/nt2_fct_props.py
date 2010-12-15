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


"""Utilities to get nt2 fct properties from py file
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))

import re
from pprint            import PrettyPrinter
from files_utils       import read, exist, write
#from nt2_base_struct   import Nt2_base_struct
from nt2_base_infos    import Nt2_base_infos
from nt2_archis_struct import Nt2_archis_struct
from nt2_tb_struct     import Nt2_tb_struct

class Nt2_fct_props(Nt2_base_infos,Nt2_tb_struct) :
    """ fct structure required by nt2 """
    Doc_beg = "[ ## list of dictionnaries for different arities of the same functor "
    Doc_dict_tpl = """
    {
    'functor' : {      ## intrinsics values related to functor
        'arity'      : '$arity$',   ## functor number of parameters
        'ret_arity'  : '$ret_arity$',  ## must be '0' or omitted if not a tuple 
        'types'      : ['real_', 'unsigned_int_', 'signed_int_'],
        'rturn'      : [ '$rturn$' ],
        'call_types' : [ $call_types$ ],
        'type_defs'  : [ $type_defs$ ],
        },
    'unit' : { ## informations for creating unit tests
        'all_parts'     : { ## common values for all the unit parts
            'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
            'stamp'       : 'modified by $author$ the $date$', ## modification stamp
        },
        'global_header' : { ## header of machin.cpp
            'included' : [],   ## list of extra include directives
            'notes'    : [],   ## list of strings that will be included in a global comment
        },
        'specific_values' : {
             'real_': {
                 'nt2::Inf<T>()' : 'nt2::Inf<r_t>()',
                 'nt2::Minf<T>()': 'nt2::Zero<r_t>()',
                 'nt2::Mone<T>()': 'nt2::Mone<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()': 'nt2::Zero<r_t>(),
             },
             'signed_int_': {
                 'nt2::Mone<T>()': 'nt2::Mone<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()': 'nt2::Zero<r_t>()',
             },
             'unsigned_int_': {
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                 'nt2::Zero<T>()': 'nt2::Zero<r_t>()',
             },
             'default' : {},   
        },
        'ranges' : {
             'default'       : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_'         : [['T(-100)','T(100)']],
             'signed_int_'   : [['T(-100)','T(100)']],
             'unsigned_int_' : [['T(0)','T(100)']],
        },
        'verif_test' : {
             'property_call' : None,
             'property_value' :{ 'default' :  ['a0'], },
             'ulp_thresh' :  ['0'], 
         },
       },
    },
    """
    Doc_end = "]"

    def __init__(self, tb_name, fct_name, mode="scalar", submode="") :
        Nt2_base_infos.__init__(self)
        Nt2_tb_struct.__init__(self)
        self.__tb_name = tb_name
        self.__fct_name = fct_name
        self.__mode = mode
        self.__fct_dict = self.__read_fct_info_dict()
        self.__fct_arities = self.__read_arities()
        self.__fct_ret_arity = self.__read_ret_arity()
        
    def get_tb_name(self)  : return self.__tb_name
    def get_fct_name(self) : return self.__fct_name   
    def get_fct_dict_list(self) :
        return self.__fct_dict if type(self.__fct_dict) is list else [self.__fct_dict]
    def get_abs_path(self,to)   : return os.path.join(self.get_nt2_path(),to)
    def get_fct_doc_path(self)  :
        return os.path.join(self.get_toolboxes_path(),
                            self.get_tb_name(),
                            'doc',self.get_fct_name()+'.py')
    def get_fct_def_path(self)  :
        return os.path.join(self.get_toolboxes_path(),
                            self.get_tb_name(),
                            'function',self.get_fct_name()+'.hpp')
    def get_fct_impl_path(self,mode)  :
        return os.path.join(self.get_toolboxes_path(),
                            self.get_tb_name(),
                            'function',mode,self.get_fct_name()+'.hpp')
    def get_fct_unit_path(self,mode)  :
        return os.path.join(self.get_toolboxes_path(),
                            self.get_tb_name(),
                            'unit',mode,self.get_fct_name()+'.cpp')


    def get_fct_arities(self) : return self.__read_arities()#self.__fct_arities
    def get_fct_ret_arity(self) : return self.__fct_ret_arity
    def get_fct_returns(self) : return "T"    ##TO DO
    def get_fct_call_types(self) : return []  ##TO DO
    def get_fct_type_defs(self) : return []   ##TO DO

    
    def __read_fct_info_dict(self) :
        p = self.get_fct_doc_path()
        print "p = %s" % p
        if not exist(p) : self.__create_fct_info_dict(p)
        s = '\n'.join(read(p))
        exec("d = "+s)
        return d

    def __create_fct_info_dict(self, force=False) :
        p = self.get_fct_doc_path()
        if not exist(p) or force:
#            s = read(os.path.join('datas', 'fct_doc.py'))
            s = self.mk_doc_from_existing_fct()
            print p
            print s
#            write(p,s)
            print "creating properties dictionnary file from template"
            print "please edit the template before using it"
            print "to create the functors files"
            raise SystemExit

    def __read_arities(self) :
        p = self.get_fct_def_path()
        print p
        arities = []
        if exist(p) :
            s = read(p)
            for l in s :
                m = re.search('  NT2_*.FUNCTION_IMPLEMENTATION',l)
                if m :
                    m = re.search('([0-9]+)\)',l)
                    if m : arities.append(int(m.groups()[0]))
        print arities
        return arities
 
    def __read_ret_arity(self) :
        p = self.get_fct_impl_path('scalar')
        print p
        if exist(p) :
            s = '/n'.join(read(p))
            return '2' if re.search('boost::fusion',s) else '0'
        else :
            return '0'
        
    def __populate_doc(self, arity) :
        doc = Nt2_fct_props.Doc_dict_tpl
        doc = re.sub('\$arity\$'     ,str(arity),doc)
        doc = re.sub('\$ret_arity\$' ,str(self.get_fct_ret_arity()),doc)
        doc = re.sub('\$rturn\$'     ,self.get_fct_returns(),doc)
        doc = re.sub('\$call_types\$',','.join(self.get_fct_call_types()),doc)
        doc = re.sub('\$type_defs\$' ,','.join(self.get_fct_type_defs()),doc)
        return doc.split('\n')
    
    def mk_doc_from_existing_fct(self) :    
        doc= [Nt2_fct_props.Doc_beg]
        for a in self.get_fct_arities(): doc += (self.__populate_doc(a))
        doc.append(Nt2_fct_props.Doc_end)
        return doc



if __name__ == "__main__" :
##    PrettyPrinter().pprint(Nt2_fct_props.get_rel_tb_tree("zorglub"))
##    PrettyPrinter().pprint(Nt2_fct_props.get_rel_tb_tree())
#    PrettyPrinter().pprint(Nt2_fct_props("exponential","pipo").get_fct_dict_list())
    PrettyPrinter().pprint(Nt2_fct_props("arithmetic","remquo").mk_doc_from_existing_fct())
sys.path.pop(0)
