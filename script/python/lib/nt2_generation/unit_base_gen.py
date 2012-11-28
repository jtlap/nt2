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
from __future__         import print_function


"""base for generation of a functor unit tests
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from nt2_fct_props import Nt2_fct_props
sys.path.pop(0)


class Base_gen(Nt2_fct_props) :
    Default_df = {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
        }
    Expansion_dict = {
    'scalar' :{
        "fundamental_":  ["uint64","int64","double","uint32","int32","float","uint16","int16","uint8","int8","bool"],	
        "arithmetic_":   ["uint64","int64","double","uint32","int32","float","uint16","int16","uint8","int8"],	
        "real_":         ["double","float"],
        "real_convert_": ["uint64","int64","double","uint32","int32","float"],
        "signed_int_":   ["int64","int32","int16","int8"],					
        "unsigned_int_": ["uint64","uint32","uint16","uint8"],			
        "integer_":      ["uint64","int64","uint32","int32","uint16","int16","int8","uint8"],				
        "signed_":       ["int64","double","int32","float","int16","int8"],				
        "int_convert_":  ["int32","int64"],
        "uint_convert_": ["uint32","uint64"],
        "sintgt_8_":     ["int16","int32","int64"],
        "uintgt_8_":     ["int16","int32","int64"],
        "int64_":        ["int64","uint64"],
        "int32_":        ["int32","uint32"],
        "int16_":        ["int16","uint16"],
        "int8_" :        ["int8","uint8"],
        "float":         ["float"],
        "double":        ["double"],
        "float_":        ["float"],
        "double_":       ["double"],
        "groupable_":    ["int16","uint16","int32","uint32","int64","uint64","double"],
        "splitable_":    ["int8","uint8","int16","uint16","int32","uint32","float"],
        "gt_8_":         ["int16","uint16","int32","uint32","int64","uint64"],
        "sintgt_8_":     ["int16","int32","int64"],
        "uintgt_8_":     ["uint16","uint32","uint64"],
        "lt_64_":        ["int16","uint16","int32","uint32","int8","uint8","float"],
        "gt_16_":        ["int32","uint32","int64","uint64","float","double"],
        "sintgt_16_":    ["int32","int64"],
        "uintgt_16_":    ["uint32","uint64"],
        },
    'sse' :{
        "fundamental_":  ["uint64","int64","double","uint32","int32","float","uint16","int16","uint8","int8","bool"],	
        "arithmetic_":   ["uint64","int64","double","uint32","int32","float","uint16","int16","uint8","int8"],	
        "real_":         ["double","float"],
        "real_convert_": ["uint64","int64","double","uint32","int32","float"],
        "signed_int_":   ["int64","int32","int16","int8"],					
        "unsigned_int_": ["uint64","uint32","uint16","uint8"],			
        "integer_":      ["uint64","int64","uint32","int32","uint16","int16","int8","uint8"],				
        "signed_":       ["int64","double","int32","float","int16","int8"],				
        "int_convert_":  ["int32","int64"],
        "uint_convert_": ["uint32","uint64"],
        "sintgt_8_":     ["int16","int32","int64"],
        "uintgt_8_":     ["int16","int32","int64"],
        "int64_":        ["int64","uint64"],
        "int32_":        ["int32","uint32"],
        "int16_":        ["int16","uint16"],
        "int8_" :        ["int8","uint8"],
        "float":         ["float"],
        "double":        ["double"],
        "float_":        ["float"],
        "double_":       ["double"],
        "groupable_":    ["int16","uint16","int32","uint32","int64","uint64","double"],
        "splitable_":    ["int8","uint8","int16","uint16","int32","uint32","float"],
        "gt_8_":         ["int16","uint16","int32","uint32","int64","uint64"],
        "sintgt_8_":     ["int16","int32","int64"],
        "uintgt_8_":     ["uint16","uint32","uint64"],
        "lt_64_":        ["int16","uint16","int32","uint32","int8","uint8","float"],
        "gt_16_":        ["int32","uint32","int64","uint64","float","double"],
        "sintgt_16_":    ["int32","int64"],
        "uintgt_16_":    ["uint32","uint64"],
        },
    'vmx' : {
        "fundamental_":  ["uint32","int32","float","uint16","int16","uint8","int8","bool"],	
        "arithmetic_":   ["uint32","int32","float","uint16","int16","uint8","int8"],	
        "real_":         ["float"],
        "real_convert_": ["uint32","int32","float"],
        "signed_int_":   ["int32","int16","int8"],					
        "unsigned_int_": ["uint32","uint16","uint8"],			
        "integer_":      ["uint32","int32","uint16","int16","int8","uint8"],				
        "signed_":       ["int32","float","int16","int8"],				
        "int_convert_":  ["int32"],
        "uint_convert_": ["uint32",],
        "sintgt_8_":     ["int16","int32"],
        "uintgt_8_":     ["int16","int32"],
        "int64_":        [],
        "int32_":        ["int32","uint32"],
        "int16_":        ["int16","uint16"],
        "int8_" :        ["int8","uint8"],
        "float":         ["float"],
        "double":        [],
        "groupable_":    ["int16","uint16","int32","uint32"],
        "splitable_":    ["int8","uint8","int16","uint16","int32","uint32","float"],
        "gt_8_":         ["int16","uint16","int32","uint32",],
        "sintgt_8_":     ["int16","int32"],
        "uintgt_8_":     ["uint16","uint32",],
        "lt_64_":        ["int16","uint16","int32","uint32","int8","uint8","float"],
        "gt_16_":        ["int32","uint32","float"],
        "sintgt_16_":    ["int32"],
        "uintgt_16_":    ["uint32",],
        },
    }
    def __init__(self, tb_name, fct_name, fct_mode) :
        Nt2_fct_props.__init__(self,tb_name,fct_name)
        self.dl = self.get_fct_dict_list()
        self.__fct_mode = fct_mode

    def get_fct_mode(self) :
        return self.__fct_mode
    def set_fct_mode(self, mode) :
        self.__fct_mode = mode
        return self.__fct_mode

    def get_fct_unit_path(self,mode = None)  :
        if mode is None : mode =self.get_fct_mode()
        return os.path.join(self.get_abs_path('toolbox'),
                            self.get_tb_name(),'unit',
                            mode,
                            self.get_fct_name()+'.cpp')

    def recover(self,st,d,default) :
        return d.get(st,default)

    def recover_info(self,st,typ,d,extra_def=None) :
        dd = d.get(st, None)
        if dd is None :
            return extra_def
        elif type(dd) is str :
            return dd
        elif dd is  None :
            return None
        else :
            return dd.get(typ, dd.get("default", None ))


    def create_unit_txt_part(self,tpl,prepare,d={},typ="",i=None) :
        """prepare prototype is    def __prepare(self,s,typ,d) : ...
        """
        r = []
        for s in tpl :
            if "$" in s :
                g = prepare(s,typ,d,i)
                if type(g) is str :
                    r.append(g)
                else :
                    r+=g
            else :
                r.append(s)
        return r

if __name__ == "__main__" :
    print(__doc__)
    print ('After: bg= Base_gen("exponential","pipo","scalar")')
    bg = Base_gen("exponential",'pipo','scalar')
    print ("bg.get_fct_name() = %s"%bg.get_fct_name())
    print ("bg.get_fct_mode() = %s"%bg.get_fct_mode())
    print ("bg.get_fct_unit_path()         = %s"%bg.get_fct_unit_path())
    print ("bg.get_fct_unit_path('scalar') = %s"%bg.get_fct_unit_path('scalar'))
    print( "bg.get_fct_unit_path('simd')   = %s"%bg.get_fct_unit_path('simd'))
    print ('After: bg= Base_gen("exponential","zz","scalar")')
    bg = Base_gen("exponential",'zz','scalar')
