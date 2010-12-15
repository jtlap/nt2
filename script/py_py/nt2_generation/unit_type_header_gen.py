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
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))

import re
from nt2_fct_props import Nt2_fct_props
from unit_base_gen import Base_gen

class Type_header_test_gen() :
    Type_Header  = [
        "",
        "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$,  $macro_types$)",
        "{",
        "  using nt2::$fct_name$;",
        "  using nt2::functors::$fct_name$_;",
        "  $type_defs$",
        "  typedef typename nt2::meta::call<$fct_name$_($call_type$)>::type r_t;",
        "  typedef typename nt2::meta::upgrade<T>::type u_t;",
        "  typedef $rturn$ wished_r_t;",
        "",
        "  // return type conformity test ",
        "  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );",
        "  std::cout << std::endl; ",
        "",
        ]
    Type_Footer   = [ "} // end of test for $type$"]
    Macros_dict = {
       "fundamental_" : "NT2_TYPES(bool)",
       "arithmetic_"  : "NT2_TYPES",
       "real_"        : "NT2_REAL_TYPES",
       "real_convert_": "NT2_REAL_CONVERTIBLE_TYPES",
       "unsigned_"    : "NT2_UNSIGNED_TYPES",
       "unsigned_int_": "NT2_UNSIGNED_TYPES", 
       "signed_int_"  : "NT2_INTEGRAL_SIGNED_TYPES",  
       "integer_"     : "NT2_INTEGRAL_TYPES",  
       "signed_"      : "NT2_SIGNED_TYPES",  
        }

    def __init__(self,base_gen,d,typ) :
        self.bg   = base_gen
        self.__gen_beg = self.__create_beg_txt(d,typ)
        self.__gen_end = self.__create_end_txt(d,typ)
        
    def get_gen_beg(self) : return  self.__gen_beg
    def get_gen_end(self) : return  self.__gen_end

    def __create_beg_txt(self,d,typ) :
        return self.bg.create_unit_txt_part(Type_header_test_gen.Type_Header,self.__prepare,d=d,typ=typ)

    def __create_end_txt(self,d,typ) :
        return self.bg.create_unit_txt_part(Type_header_test_gen.Type_Footer,self.__prepare,d=d,typ=typ)

    def __macro(self,typ) :
        if typ in Type_header_test_gen.Macros_dict.keys() :
            return Type_header_test_gen.Macros_dict[typ]
        elif typ[-2:] =="_t" :
            return "(nt2::"+typ+")"
        else :
            return "("+typ+")"

    def __get_call_types(self,d) :
        dd = d["functor"].get("call_types",None)
        if dd is None or len(dd)==0:
            return ','.join(["T"]*int(d["functor"].get("arity","1")))
        else :
            return ','.join(dd)

    def __prepare(self,s,typ,d) :
        s=re.sub("\$fct_mode\$",self.bg.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.bg.get_tb_name(),s)
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
        s=re.sub("\$macro_types\$",self.__macro(typ),s)
        s=re.sub("\$type\$"    ,typ,s)
        s=re.sub("\$arity\$"   ,str(d["functor"]["arity"]),s)
        s=re.sub("\$call_type\$", self.__get_call_types(d),s)
        s=re.sub("\$rturn\$", d["functor"]["rturn"].get(typ,d["functor"]["rturn"]["default"]),s)
        m = re.match("( *)\$type_defs\$.*",s)
        if m :
            s = []
            beg = m.groups()[0]
            tpdefs = d["functor"].get("type_defs",None)
            if tpdefs is not None :
                for l in tpdefs :
                    s.append( beg+l)
            else :
                s= ""
        return s

if __name__ == "__main__" :
    from pprint        import PrettyPrinter
    from unit_base_gen import Base_gen
    print __doc__
    bg = Base_gen("exponential",'pipo','scalar')
    dl = bg.get_fct_dict_list()
    r = []
    for d in dl :
        types = bg.recover("types",d["functor"],[])
        for typ in types :
            thg = Type_header_test_gen(bg,d,typ)
            r+=thg.get_gen_beg()
            r+=thg.get_gen_end()
    PrettyPrinter().pprint(r)

sys.path.pop(0)
sys.path.pop(0)
