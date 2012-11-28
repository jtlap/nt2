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


"""generation of a global include header for functor unit tests
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from unit_base_gen import Base_gen
sys.path.pop(0)
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_adding"))
from headerfiles import Headers
sys.path.pop(0)

import re
import datetime

class Bench_gen() :
    def __init__(self, base_gen,simd_type='sse') :
        self.bg   = base_gen
        self.__simd_type = simd_type
        self.mode = self.bg.get_fct_mode()
        self.__gen_result = self.__create_unit_txt()

    def get_gen_result(self) : return  self.__gen_result

    def __create_unit_txt(self) :
        """ auxilliary of create_bench
        """
        name = self.bg.get_fct_name()
        tb_name = self.bg.get_tb_name()
        package = 'boost/simd' if tb_name.find('.') != -1 else 'nt2'
        nspce   = 'boost::simd'if tb_name.find('.') != -1 else 'nt2'
        mode = self.bg.get_fct_mode()
        nsp = "" if self.bg.get_tb_style()=="sys" else tb_name+'::'
        txt = [
            '#define NT2_BENCH_MODULE "nt2 %s toolbox - %s/%s Mode"'%(tb_name,name,mode),
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// timing Test behavior of %s components in %s mode"%(tb_name,mode),
            "//////////////////////////////////////////////////////////////////////////////",
            ""
            "#include <%s/include/%s.hpp>"%(self.bg.demangle(tb_name,'toolbox'),name.lower()),
            "#include <%s/sdk/unit/benchmark.hpp>"%package,
            "#include <%s/sdk/unit/bench_includes.hpp>"%package,
            "#include <boost/dispatch/meta/as_integer.hpp>",
            "#include <%s/include/constants/digits.hpp>"%package,
            "#include <cmath>",
            "" if mode=='scalar' else "typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;",
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// %s runtime benchmark for functor<%s_> from %s"%(mode,name,tb_name),
            "//////////////////////////////////////////////////////////////////////////////",
            "using %s::%stag::%s_;"%(nspce,nsp,name.lower()),
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// range macro",
            "//////////////////////////////////////////////////////////////////////////////",
            "#define RS(T,V1,V2) (T, %(T)s(V1) ,%(T)s(V2))"% {"T" :"" if mode=='simd' else "T"},
            "",
            ]
        txtf = [
            "",
            "#undef RS",
            "",
            ]
        dl = self.bg.get_fct_dict_list()
        k=1
        r = []
        for d in dl :
            d1 = d.get('bench',False)
            if d1 :
                pass
            else :
                d1 = { "arity"  : int(d["functor"]["arity"]),
                       "ranges" : d["unit"].get("ranges",[['0','1']]),
                       "types"  : d["functor"].get('types',['T']),
                       "simd_types"  : d["functor"].get('simd_types',d["functor"].get('types',['T'])),
                       "type_defs": d["functor"].get('type_defs',[]),
                       "call_types" :d["functor"]["call_types"],
                       }
                if d1["call_types"] == [] : d1["call_types"] = ["T"]
##            PrettyPrinter().pprint(d1)

            if True :
                tpl = d["functor"].get("tpl","")
                call =  "  NT2_TIMING(%s_%s,%s)" % (name,tpl,"%s")
                variety = { 'real_'         : ["float","double"],
                            'signed_int_'   : ["nt2::int8_t","nt2::int16_t","nt2::int32_t","nt2::int64_t"],
                            'unsigned_int_' : ["nt2::uint8_t","nt2::uint16_t","nt2::uint32_t","nt2::uint64_t"],
                            'float'         : ["float"],
                            'double'        : ["double"],
                            'float_'        : ["float"],
                            'double_'       : ["double"],
                            'integer_'      : ["nt2::int8_t","nt2::int16_t","nt2::int32_t","nt2::int64_t","nt2::uint8_t","nt2::uint16_t","nt2::uint32_t","nt2::uint64_t"],
                            'int32_t'       : ["nt2::int32_t"],
                            'int64_t'       : ["nt2::int64_t"],
                            'uint32_t'      : ["nt2::uint32_t"],
                            'uint64_t'      : ["nt2::uint64_t"],
                            'int64_'        : ["nt2::uint64_t","nt2::int64_t"],
                            'int32_'        : ["nt2::uint32_t","nt2::int32_t"],
                            'int16_'        : ["nt2::uint16_t","nt2::int16_t"],
                            'int8_'         : ["nt2::uint8_t","nt2::int8_t"],
                            "groupable_"    : ["nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t","double"],
                            "splitable_"    : ["nt2::int8_t","nt2::uint8_t","nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","float"],
                            "gt_8_"         : ["nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t","double","float"],
                            "lt_64_"        : ["nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","nt2::int8_t","nt2::uint8_t","float"],
                            "gt_16_"        : ["nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t","float","double"],
                            "sintgt_16_"    : ["nt2::int32_t","nt2::int64_t"],
                            "uintgt_16_"    : ["nt2::uint32_t","nt2::uint64_t"],
                            "int_convert_"  : ["nt2::int32_t","nt2::int64_t"],
                            "uint_convert_" : ["nt2::uint32_t","nt2::uint64_t"],
                            "sintgt_8_"      : ["nt2::int16_t","nt2::int32_t","nt2::int64_t"],
                             }
                typs = d1["simd_types"] if mode == 'simd' else d1["types"]
                if self.__simd_type == 'altivec' and mode ==  'simd' :
                     variety[ 'real_']= ["float"]
                     variety[ 'double'] = []
                     variety[ 'double_'] = []
                     variety[ "gt_16_" ] = ["nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t","float","double"]
                     variety[ "groupable_"] = ["nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t"]
                     variety[ "gt_8_"] = ["nt2::int16_t","nt2::uint16_t","nt2::int32_t","nt2::uint32_t","nt2::int64_t","nt2::uint64_t","double","float"]

                print ("typs %s" % typs)
                for typ in typs :
##                    print("typ = %s, variety = %s"%(typ,variety[typ]))
                    for t in variety[typ] :
                        def get_ranges(typ, variety) :
##                            print ("in get_ranges")
##                            print ("d1['ranges'] %s"% d1["ranges"])
                            d = d1["ranges"]
                            if t in d.keys() :
                                rges = d[t]
                            elif typ in d.keys() :
                                rges = d[typ]
                            elif "default" in d.keys() :
                                rges = d["default"]
                            else :
                                rges = None
                            return rges
                        ##   rges = d1["ranges"].get(t,d1["ranges"].get("default",None))
                        rges =  get_ranges(typ, variety)
##                        print("rges %s"%rges)
                        r += ["namespace n%s {"%str(k) ]
                        k+=1;
                        r.append("  typedef %s T;"%t )
                        r.append("  typedef T sT;")
                        r.append("  typedef boost::dispatch::meta::as_integer<T>::type iT;")
##                        r += ["  "+td for td in d1["type_defs"]]
                        if mode == "simd" :
                            r += ["  typedef boost::simd::native<%s,ext_t> v%s;"%(ct,ct)  for ct in d1["call_types"] if ct[0] != 's' ]
                        tpl = "(RS(%s,%s,%s))"
##                        print( 'd1["ranges"] %s'%d1["ranges"])
##                        print("rges  %s"%rges)
##                        if isinstance(rges[0][0],list) : print(rges)
                        if not isinstance(rges[0][0],list) : rges = [rges]
                        prefix = "v" if mode == 'simd' else ''
                        scalar_ints = d['functor'].get('scalar_ints',False) == 'True'
                        iprefix = "v" if (mode == 'simd' and (name[-1]!='i') and (not scalar_ints)) else ''
                        calls = d1["call_types"]*d1["arity"] if len( d1["call_types"]) == 1 else d1["call_types"][0:int(d1["arity"])]
                        if isinstance(calls,str) : calls = [calls]
##                        print("callls %s"%calls)
                        for rgen in rges :
##                            print("rgen %s"%rgen)
                            param=""
                            for j,rge in enumerate(rgen) :
##                                print("calls[%s] = %s"%(j,calls[j]))
                                if calls[j][0]=='i' :
                                    param += tpl%(iprefix+calls[j],rge[0],rge[1])
                                elif   calls[j][0]=='s' :
                                   param += tpl%(calls[j][1:],rge[0],rge[1])
                                else :
                                    param += tpl%(prefix+calls[j],rge[0],rge[1])
                            r.append(call%param)
                        r += ["}"]

        txt += r+txtf;
        if tb_name.find('.') != -1 :
            for i,l in enumerate(txt) :
                txt[i]=re.sub('nt2::','boost::simd::',l)
        h = Headers(os.path.join(self.bg.get_nt2_rel_tb_path(tb_name),'bench',mode),
                    name,inner=txt,guard_begin=[],guard_end=[]).txt()
        return h.split('\n')

if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    bg = Base_gen("exponential",'pipo','simd')
    bbg = Bench_gen(bg)
    PrettyPrinter().pprint(bbg.get_gen_result())
