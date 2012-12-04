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
    Default_df = {
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::result_of<nt2::meta::floating(T)>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_'],
        }
    Type_Header  = {
      "default" : {
        "scalar" :
        [
            "",
            "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$_$rank$,  $macro_types$)",
            "{",
            "  $special$",
            "  using nt2::$tb_style_base$$fct_name_repl$;",
            "  using nt2::$tb_style_base$tag::$fct_name$_;",
            "  $type_defs$",
            "  typedef typename nt2::meta::as_integer<T>::type iT;",
            "  typedef typename nt2::meta::call<$fct_name$_$tpl$($call_type$)>::type r_t;",
            "  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;",
            "  typedef typename nt2::meta::upgrade<T>::type u_t;",
            "  typedef $rturn$ wished_r_t;",
            "  $type_defs_aft$",
            "",
            "  // return type conformity test ",
            "  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );",
            "  std::cout << std::endl; ",
            "  double ulpd;",
            "  ulpd=0.0;",
            "  boost::dispatch::ignore_unused(ulpd);"
            "",
            ],
        "simd" :
        [
            "",
            "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$_$rank$,  $macro_types$)",
            "{",
            "  using nt2::$tb_style_base$$fct_name_repl$;",
            "  using nt2::$tb_style_base$tag::$fct_name$_;",
            "  using nt2::load; ",
            "  using boost::simd::native;",
            "  using nt2::meta::cardinal_of;",
            "  $type_defs$",
            "  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;",
            "  typedef typename nt2::meta::upgrade<T>::type   u_t;",
            "  typedef native<T,ext_t>                        n_t;",
            "  typedef n_t                                     vT;",
            "  typedef typename nt2::meta::as_integer<T>::type iT;",
            "  typedef native<iT,ext_t>                       ivT;",
            "  typedef typename nt2::meta::call<$fct_name$_$tpl$($call_type$)>::type r_t;",
            "  typedef typename nt2::meta::call<$fct_name$_$tpl$($scall_type$)>::type sr_t;",
            "  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;",
            "  double ulpd;",
            "  ulpd=0.0;",
            "  boost::dispatch::ignore_unused(ulpd);"
            "",
            ]
        },
      "boost"   :
        {
          "scalar" :
           [
            "",
            "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$_$rank$,  $macro_types$)",
            "{",
            "  $special$",
            "  using boost::simd::$tb_style_base$$fct_name_repl$;",
            "  using boost::simd::$tb_style_base$tag::$fct_name$_;",
            "  $type_defs$",
            "  typedef typename boost::dispatch::meta::as_integer<T>::type iT;",
            "  typedef typename boost::dispatch::meta::call<$fct_name$_$tpl$($call_type$)>::type r_t;",
            "  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;",
            "  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;",
            "  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;",
            "  typedef $rturn$ wished_r_t;",
            "  $type_defs_aft$",
            "",
            "  // return type conformity test ",
            "  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );",
            "  std::cout << std::endl; ",
            "  double ulpd;",
            "  ulpd=0.0;",
            "  boost::dispatch::ignore_unused(ulpd);"
            "",
            ],
        "simd" :
        [
            "",
            "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$_$rank$,  $macro_types$)",
            "{",
            "  using boost::simd::$tb_style_base$$fct_name_repl$;",
            "  using boost::simd::$tb_style_base$tag::$fct_name$_;",
            "  using boost::simd::load; ",
            "  using boost::simd::native;",
            "  using boost::simd::meta::cardinal_of;",
            "  $type_defs$",
            "  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;",
            "  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;",
            "  typedef native<T,ext_t>                        n_t;",
            "  typedef n_t                                     vT;",
            "  typedef typename boost::dispatch::meta::as_integer<T>::type iT;",
            "  typedef native<iT,ext_t>                       ivT;",
            "  typedef typename boost::dispatch::meta::call<$fct_name$_$tpl$($call_type$)>::type r_t;",
            "  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;",
            "  typedef typename boost::simd::meta::scalar_of<r_t>::type ssr_t;",
            "  double ulpd;",
            "  ulpd=0.0;",
            "  boost::dispatch::ignore_unused(ulpd);"
            "",
            ]
        },
      }

    Type_Footer   = [ "} // end of test for $type$"]
    Macros_dict = {
       "fundamental_" : "NT2_TYPES(bool)",
       "arithmetic_"  : "NT2_TYPES",
       "real_"        : "NT2_REAL_TYPES",
       "real_convert_": "NT2_REAL_CONVERTIBLE_TYPES",
       "int_convert_" : "NT2_INT_CONVERT_TYPES",
       "uint_convert_": "NT2_UINT_CONVERT_TYPES",
       "unsigned_"    : "NT2_UNSIGNED_TYPES",
       "unsigned_int_": "NT2_UNSIGNED_TYPES",
       "signed_int_"  : "NT2_INTEGRAL_SIGNED_TYPES",
       "integer_"     : "NT2_INTEGRAL_TYPES",
       "signed_"      : "NT2_SIGNED_TYPES",
       "int64_"       : "NT2_INT_64_TYPES",
       "int32_"       : "NT2_INT_32_TYPES",
       "int16_"       : "NT2_INT_16_TYPES",
       "int8_"        : "NT2_INT_8_TYPES",
       "groupable_"   : "NT2_GROUPABLE_TYPES",
       "splitable_"   : "NT2_SPLITABLE_TYPES",
       "gt_8_"        : "NT2_INT_GT8_TYPES",
       "sintgt_8_"    : "NT2_SIGNED_INT_GT_8_TYPES",
       "uintgt_8_"    : "NT2_UNSIGNED_INT_GT_8_TYPES",
       "lt_64_"       : "NT2_LT64_TYPES",
       "gt_16_"       : "NT2_GT16_TYPES",
       "sintgt_16_"   : "NT2_SIGNED_INT_GT_16_TYPES",
       "uintgt_16_"   : "NT2_UNSIGNED_INT_GT_16_TYPES",
        }

    def __init__(self,base_gen,d,typ,rank) :
        self.bg   = base_gen
        self.mode = self.bg.get_fct_mode()
        self.__rank = rank
        self.__module =  d["functor"].get("module",'default')
        if self.__module != 'boost' : self.__module = 'default'
        self.__gen_beg = self.__create_beg_txt(d,typ)
        self.__gen_end = self.__create_end_txt(d,typ)

    def get_gen_beg(self) : return  self.__gen_beg
    def get_gen_end(self) : return  self.__gen_end

    def __create_beg_txt(self,d,typ) :
        return self.bg.create_unit_txt_part(Type_header_test_gen.Type_Header[self.__module][self.mode],self.__prepare,d=d,typ=typ)

    def __create_end_txt(self,d,typ) :
        return self.bg.create_unit_txt_part(Type_header_test_gen.Type_Footer,self.__prepare,d=d,typ=typ)

    def __macro(self,typ,mode='scalar') :
        if typ in Type_header_test_gen.Macros_dict.keys() :
            r = Type_header_test_gen.Macros_dict[typ]
        elif typ[-2:] =="_t" :
            r = "(nt2::"+typ+")"
        else :
            r = "("+typ+")"
        if mode == "simd" :
            r = re.sub("NT2_(.*?)TYPES","NT2_SIMD_\\1TYPES",r)
            r = re.sub("(bool)","",r)
##        print("r = %s"%r)
        if self.__module == 'boost' : r = re.sub("NT2","BOOST_SIMD",r)
        return r

    def __get_call_types(self,d) :
        df = d.get("functor", self.Default_df)
        dd = df.get("call_types",None)
        t = "T" if self.mode == 'scalar' else "vT"
        if dd is None or len(dd)==0:
            r = ','.join([t]*int(df.get("arity","1")))
        elif self.mode == 'simd' :
            r = re.sub("T","vT",','.join(dd))
        else :
            r = ','.join(dd)
        if self.bg.get_fct_name()[-1]=='i' or d["functor"].get("scalar_ints",False) :
            r = re.sub("ivT","iT",r)
        return r

    def __get_scall_types(self,d) :
        df = d.get("functor", self.Default_df)
        dd = df.get("call_types",None)
        t = "T"
        if dd is None or len(dd)==0:
            r = ','.join([t]*int(df.get("arity","1")))
        else :
            r = ','.join(dd)
        return r

    def __get_special(self,d) :
        df = d.get("functor", self.Default_df)
        if not df : return ""
        special = df.get("special",[""])
        return "using nt2::rn;" if special[0] == "crlibm" else ""

    def __get_tpl(self,d) :
        df = d.get("functor", self.Default_df)
        if not df : return ""
        special = df.get("special",[""])
        name = self.bg.get_fct_name()
        if special[0] == "crlibm" and not( name[-3:] in ['_rd','_rn','_ru','_rz']) :
            return "<rn>"
        else :
            return df.get("tpl","")

    def __prepare(self,s,typ,d,i=None) :
        df = d.get("functor", self.Default_df)
        style = self.bg.get_tb_style()
        n = self.bg.get_fct_name()
        n_repl= df.get("name",False)
        if not n_repl : n_repl = n
        tb_style_base = "" if style =="sys" else self.bg.get_tb_name()+'::'
        s=re.sub("\$special\$",self.__get_special(d),s)
        s=re.sub("\$tpl\$",self.__get_tpl(d),s)
        s=re.sub("\$tb_style_base\$",tb_style_base,s)
        s=re.sub("\$fct_mode\$",self.bg.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.bg.get_tb_name(),s)
        s=re.sub("\$fct_name\$",n,s)
        s=re.sub("\$fct_name_repl\$",n_repl,s)
        s=re.sub("\$macro_types\$",self.__macro(typ,self.bg.get_fct_mode()),s)
        s=re.sub("\$type\$"    ,typ,s)
        s=re.sub("\$arity\$"   ,str(df.get("arity","1")),s)
        s=re.sub("\$rank\$"   ,str(self.__rank),s)
        s=re.sub("\$call_type\$", self.__get_call_types(d),s)
        s=re.sub("\$scall_type\$", self.__get_scall_types(d),s)
        s=re.sub("\$rturn\$", df.get("rturn").get(typ,df["rturn"]["default"]),s)
        m = re.match("( *)\$type_defs\$.*",s)
        if m :
            r = []
            beg = m.groups()[0]
            tpdefs = df.get("type_defs",None)
            if tpdefs is not None :
                for l in tpdefs :
                    r.append( beg+l)
            else :
                r = ""
            return r
        m = re.match("( *)\$type_defs_aft\$.*",s)
        if m :
            r = []
            beg = m.groups()[0]
            tpdefs = df.get("type_defs_aft",None)
            if tpdefs is not None :
                for l in tpdefs :
                    r.append( beg+l)
            else :
                r = ""
            return r
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
