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
import datetime
from pprint            import PrettyPrinter
from files_utils       import read, exist, write
#from nt2_base_struct   import Nt2_base_struct
from nt2_base_infos    import Nt2_base_infos
from nt2_archis_struct import Nt2_archis_struct
from nt2_tb_struct     import Nt2_tb_struct
from nt2_fct_props     import Nt2_fct_props
from nt2_fct_internals import Nt2_fct_internals

class Nt2_fct_doc(Nt2_fct_props) :
    """ constructing pydoc from existing fct or from scratch """
    Doc_beg = [ "[  ## list of dictionnaries for different arities of the same functor"]
    Doc_end = [ "]"]
    Doc_tpl = """{
    'functor' : {      ## intrinsics values related to $fct_name$
$functor$,
    },
    'unit'    : { ## informations for creating unit tests
        'global_header' : { ## properties needed to construct header of $fct_name$.cpp
$global_header$
        },
        'specific_values' : { ## parameters/values pairs to be asserted
                              ## one parameter (no commas) is replicated else use comma separated string
                              ## a specific ulp for a value can be introduced in the string result after a comma
                              ## or in a dictionnary {'result' : '...','ulp_thresh','...'}
$specific_values$
        },
        'verif_test' : { ## assert result of property call equal to property values
                         ## up to ulp_threshold (0 means strict equality) for random
                         ## values uniformly distributed in ranges
$verif_test$
        },
    },
},"""
    Doc_functor = """\
        'arity'      : '$arity$',  ## functor number of parameters
        'ret_arity'  : '$ret_arity$',            ## must be '0' or omitted or None if not a tuple 
        'types'      : [ $types$ ],  ## list of types for which a specific test will be generated
        'rturn'      : $rturn$,  ## dictionnary of calls return types for each of <types>
        'call_types' : [ $call_types$ ],  ## list of types for one call [] default to 'T'
        'type_defs'  : [ $type_defs$ ],  ## list of additional typedef needed (for examples for <call_types>"""
    Doc_global_header = """\
        'first_stamp' : 'created  by $author$ the $date$', ## creation stamp
        'stamp'       : 'modified by $author$ the $date$', ## modification stamp
        'included'    : [$included$],   ## list of extra include directives
        'notes'       : [],   ## list of strings that will be included in a global comment"""
    Doc_specific_values_dict = {
        'real_'       : 
            """\
            'nt2::Inf<T>()' :  {'result' : 'nt2::Inf<r_t>()' ,'ulp_thresh':'0'},
            'nt2::Minf<T>()':  {'result' : 'nt2::Minf<r_t>()','ulp_thresh':'0'},
            'nt2::Mone<T>()':  {'result' : 'nt2::Mone<r_t>()','ulp_thresh':'0'},
            'nt2::Nan<T>()' :  {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
            'nt2::One<T>()' :  {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
            'nt2::Zero<T>()':  {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},""",
        'signed_int_': 
            """\
            'nt2::Mone<T>()': {'result' : 'nt2::Mone<r_t>()','ulp_thresh':'0'},
            'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
            'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},""",
        'default': 
            """\
            'nt2::One<T>()' : {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
            'nt2::Zero<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},""",
        'bool_': 
            """\
            'nt2::True<T>()' : {'result' : 'nt2::One<r_t>()' ,'ulp_thresh':'0'},
            'nt2::False<T>()': {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},""",
        }
    
    Doc_verif_test = (
    """\
        'property_call' : None,
        'property_value' :{ 'default' :  ['a0'], },
        'ulp_thresh'     :{ 'default' :   ['0'], }, 
        'nb_rand'        :{ 'default' : '$nb_rand$' },  ## number of generated tests 
        'ranges' : {
             'default'       : $default$, 
             'real_'         : $real_$,   
             'signed_int_'   : $signed_int_$,
             'unsigned_int_' : $unsigned_int_$, 
         },""")
    def __init__(self, tb_name, fct_name, mode="scalar", submode="") :
        Nt2_fct_props.__init__(self,tb_name, fct_name, mode, submode)
        self.adds = {}
        self.ranges={}
        self.ad_hoc_modifications()
        self.add_includes()
        self.ad_hoc_ranges()
        
    def add_includes(self) :
        inc_p = "constants.hpp" 
        if exist(os.path.join(self.get_include_path(),inc_p)) :
            rel_inc_p =rel_path = os.path.join('nt2/toolbox/',self.get_tb_name(),'include',inc_p)
            self.adds["included"] = [ "'#include <%s>'"%rel_inc_p]

    def ad_hoc_ranges(self) :
        if self.get_tb_name() == 'trigonometric' :
            if self.get_fct_name()[0] =="a" :
                r = "[['T(-1)','T(1)']]"
                rsi = r
                rui ="[['T(0)','T(1)']]"
            elif self.get_fct_name()[-1] =='i' :
                r = "[['T(-10)','T(10)']]"
                rsi = r
                rui ="[['T(0)','T(10)']]"
            elif self.get_fct_name()[-1] =='d' :
                r = "[['T(-1800)','T(1800)']]"
                rsi = "[['T(-128)','T(127)']]"
                rui ="[['T(0)','T(127)']]"
            else :
                r = "[['T(-10*nt2::Pi<T>())','T(100*nt2::Pi<T>())']]"
                rsi ="[['T(-32)','T(32)']]"
                rui ="[['T(0)','T(32)']]"
        else :
            r = "[['T(-100)','T(100)']]"
        self.ranges["real_"] = r
        self.ranges["default"] = "[['nt2::Valmin<T>()', 'nt2::Valmax<T>()']]"
        self.ranges["signed_int_"] = rsi
        self.ranges["unsigned_int_"] = rui
        
    def ad_hoc_modifications(self) :        
        if (self.get_tb_name() == 'trigonometric' and self.get_fct_name()[0] !="a") :
            if self.get_fct_name()[-1] =='i' :
                Nt2_fct_doc.Doc_specific_values_dict['real_'] =\
                """\
                'nt2::Inf<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Minf<T>()'    : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Nan<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::One<T>()'     : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Half<T>()'    : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Quarter<T>()' : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Mone<T>()'    : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Mhalf<T>()'   : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-nt2::Quarter<T>()': {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Zero<T>()'    : {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},"""
            elif self.get_fct_name()[-1] == 'd':
                Nt2_fct_doc.Doc_specific_values_dict['real_'] =\
                """\
                'nt2::Inf<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Minf<T>()'    : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Nan<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'T(180)'            : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'T(90)'             : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'T(45)'             : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-T(180)'           : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-T(90)'            : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-T(45)'             : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Zero<T>()'    : {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},"""
            else :
                Nt2_fct_doc.Doc_specific_values_dict['real_'] =\
                """\
                'nt2::Inf<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Minf<T>()'    : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Nan<T>()'     : {'result' : 'nt2::Nan<r_t>()' ,'ulp_thresh':'0'},
                'nt2::Pi<T>()'      : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Pi_o_2<T>()'  : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Pi_o_4<T>()'  : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-nt2::Pi<T>()'     : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-nt2::Pi_o_2<T>()' : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                '-nt2::Pi_o_4<T>()' : {'result' : 'nt2::Zero<T>()'  ,'ulp_thresh':'0'},
                'nt2::Zero<T>()'    : {'result' : 'nt2::Zero<r_t>()','ulp_thresh':'0'},"""
                  
            PrettyPrinter().pprint(type(Nt2_fct_doc.Doc_specific_values_dict["real_"]))

    def mk_fct_doc_tpl(self,
                       doc_tpl=None,
                       doc_functor=None,
                       doc_global_header=None,
                       doc_specific_values=None,
                       doc_verif_test=None,
                       arity = '1') :
        n = 4
        if doc_tpl             is None : doc_tpl = Nt2_fct_doc.Doc_tpl
        if doc_functor         is None : doc_functor = (' '*n)+Nt2_fct_doc.Doc_functor.replace('\n', '\n'+' '*n)
        if doc_global_header   is None : doc_global_header = (' '*n)+Nt2_fct_doc.Doc_global_header.replace('\n', '\n'+' '*n)
        if doc_specific_values is None :
            doc_specific_values = self.__specif_vals(Nt2_fct_internals.get_returns(self.get_fct_text()).keys(),n,arity)
        if doc_verif_test      is None : doc_verif_test = (' '*n)+Nt2_fct_doc.Doc_verif_test.replace('\n', '\n'+' '*n)
        s = doc_tpl
        s = re.sub('\$functor\$', doc_functor,s)
        s = re.sub('\$global_header\$', doc_global_header,s)
        s = re.sub('\$specific_values\$', doc_specific_values,s)
        s = re.sub('\$verif_test\$', doc_verif_test,s)
        return s

    def mk_doc_from_existing_fct(self,mk_doc_tpl=None) :
#        if doc_tpl is None : doc_tpl = self.mk_fct_doc_tpl()
        doc= Nt2_fct_doc.Doc_beg
        for a in self.get_fct_arities():
            adoc = self.__populate_doc(mk_doc=mk_doc_tpl,arity=a)
            doc += adoc
        doc += Nt2_fct_doc.Doc_end
        return doc

    def create_fct_pydoc_file(self, force=False,error='warn') :
        p = self.get_fct_doc_path()
        if not exist(p) or force:
            s = self.mk_doc_from_existing_fct()
            PrettyPrinter().pprint(s)
#            write(p,s)
            print("creating properties dictionnary file from template")
            print("please edit the template before using it")
            print("to create the functors files")
            if error == 'exit' : raise SystemExit
        else :
            print("file exist")
##            s = self.mk_doc_from_existing_fct()
##            PrettyPrinter().pprint(s)

    def __populate_doc(self, mk_doc=None,arity=None) :
        if mk_doc is None :
            doc = self.mk_fct_doc_tpl(arity=arity)
        else :
            doc = mk_doc(arity=arity)
        n = 4
        doc = re.sub('\$arity\$'     ,str(arity),doc)
        doc = re.sub('\$fct_name\$'  ,self.get_fct_name(),doc)
        doc = re.sub('\$ret_arity\$' ,str(self.get_fct_ret_arity()),doc)
        doc = re.sub('\$rturn\$'     ,self.__reformat(self.get_fct_returns(),3*n),doc)
        doc = re.sub('\$call_types\$',','.join(self.get_fct_call_types()),doc)
        doc = re.sub('\$type_defs\$' ,','.join(self.get_fct_type_defs()),doc)
        doc = re.sub('\$author\$'    , self.get_author(),doc)
        doc = re.sub('\$date\$'      , datetime.datetime.now().strftime("%d/%m/%Y"),doc)
        doc = re.sub('\$nb_rand\$'   , '100',doc)
        doc = re.sub('\$types\$'     , ','.join(self.get_fct_types()),doc)
        doc = re.sub('\$included\$'  , ','.join(self.adds.get("included",[])),doc)
        for k in ["real_","signed_int_","unsigned_int_","default"] :
            doc = re.sub('\$'+k+'\$'  , self.ranges.get(k,[]),doc)
        return doc.split('\n')
    
    def __reformat(self,d,n) :
        s = PrettyPrinter().pformat(d)
        s1 = s.split('\n')
        s2 = [s1[0]]
        for s in s1[1:] : s2.append(' '*27+s)
        return '\n'.join(s2)

    @classmethod
    def __specif_vals(cls,typ_tags,n,arity='1') :
        r = []
        for typ_tag in typ_tags :
            r +=  ["%s'%s' : {" %(' '*(n+8),typ_tag)]
            r +=  cls.__specif_val(typ_tag,n,arity)
            r += ["%s },"% (' '*(n+8))]
        return '\n'.join(r)
  
    @classmethod
    def __specif_val(cls,typ_tag,n,arity='1') :
        r = Nt2_fct_doc.Doc_specific_values_dict[cls.__choose(typ_tag)]
        r1 = [ ' '*n+t for t in r.split('\n')]
        if arity == 1 : return r1
        r2= []
        for t in r1 :
            m = re.match(" *'(.*?)'",t)
            r2 += [t.replace(m.group(1),', '.join([m.group(1)]*arity))]
        return r2    


    @classmethod
    def __choose(cls,typ_tag) :
         if typ_tag in ('fundamental_','real_','float','double') :
             return 'real_'
         elif typ_tag == 'bool_' :
             return 'bool_'
         elif typ_tag in ('signed_int_','signed_','int_64_t','int32_t','int16_t','int8_t') :
             return 'signed_int_'
         else :
             return 'default'
if __name__ == "__main__" :
    from nt2_tb_props import Nt2_tb_props
    tb_name = "trigonometric"
    fcts = Nt2_tb_props(tb_name).get_fcts_list()
    for fct in fcts :
        nfd = Nt2_fct_doc(tb_name,fct)
        nfd.create_fct_pydoc_file()
sys.path.pop(0)
    
