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
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))

import re
from nt2_fct_props import Nt2_fct_props
from unit_base_gen import Base_gen

class Specific_values_test_gen(Base_gen) :
##    Spec_values_tuple_tpl = "  NT2_TEST_%sEQUAL(  $fct_name$($call_param_vals$), $call_param_res$, $specific_thresh$);"
    def __init__(self, base_gen,d,typ,ret_arity,mode) :
        self.mode = mode
        self.bg = base_gen
        if ret_arity <= 1 :
            self.__gen_result = self.__create_values_test(d,typ)
        else :
            self.__gen_result = self.__create_tuple_values_test(d,typ,ret_arity)

    def get_gen_result(self) : return  self.__gen_result

    def __create_values_test(self,dl,typ) :
#####        print("typ = %s"%typ)
        d = dl['unit']["specific_values"]
#####        print("d=== %s"%d)
        dd = d.get(typ,d.get("default",None))
        r = ["", "  // specific values tests"]
        no_ulp = dl["unit"]["global_header"].get("no_ulp",False)
        no_ulp = False if no_ulp == 'False' else no_ulp
        ulp_str = "" if no_ulp else "ULP_"
        thresh_str = "" if no_ulp else ", $specific_thresh$"
        if self.mode == 'simd' :
            if dl["functor"].get('special',[''])[0]=='predicate' :
                Spec_values_tpl = "  NT2_TEST_%sEQUAL($fct_name$($call_param_vals$)[0]!=0, $call_param_res$%s);"
            else :
                Spec_values_tpl = "  NT2_TEST_%sEQUAL($fct_name$($call_param_vals$)[0], $call_param_res$%s);"
        else :
            Spec_values_tpl = "  NT2_TEST_%sEQUAL($fct_name$($call_param_vals$), $call_param_res$%s);"
#####        print("dd-------- %s"%dd)
        for k in sorted(dd.keys()) :
            s = Spec_values_tpl%  (ulp_str,thresh_str)
            s =re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
            if k.count(',')==0 : ## one for all but no , !
                g = ', '.join([k]*int(dl["functor"]["arity"]))
            else :                 ## regular call parameters list
                g = k
            if self.mode == 'simd' :
                g =re.sub("T","vT",g)
                g =re.sub("vT\(","nt2::splat<vT>(",g)
            s =re.sub("\$call_param_vals\$",g,s)
            if type(dd[k]) is str :
                rep = dd[k]
                thr = '0'
            elif type(dd[k]) is dict :
               rep = dd[k]["result"]
               thr = dd[k].get("ulp_thresh",'1.0')
            else :
                rep = dd[k][0]
                thr = dd[k][1]
            if self.mode == 'simd' :
                rep =re.sub("r_t","sr_t",rep)
            s =re.sub("\$call_param_res\$",rep,s)
            s =re.sub("\$specific_thresh\$",thr,s)
            r.append(s)
        return r

    def __create_tuple_values_test(self,dl,typ,ret_arity) :
        no_ulp = dl["unit"]["global_header"].get("no_ulp",False)
        no_ulp = False if no_ulp == 'False' else no_ulp
        if no_ulp :
            Call = "    NT2_TEST_EQUAL( boost::fusion::get<$i$>(res), $call_param_res$);"
        else :
            Call = "    NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<$i$>(res), $call_param_res$, $specific_thresh$);"

        Results = "    r_t res = $fct_name$($call_param_vals$);"
        d = dl['unit']["specific_values"]
        dd = d.get(typ,d.get("default",None))
        r = ["",
             "  // specific values tests",]
        for i in range(ret_arity) :
            r.append("  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,%s>::type>::type r_t%s;"%(str(i),str(i)))

        for k in sorted(dd.keys()) :
            s = Results
            s =re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
            if k.count(',')==0 : ## one for all but no , !
                g = ', '.join([k]*int(dl["functor"]["arity"]))
            else :                 ## regular call parameters list
                g = k
            s =re.sub("\$call_param_vals\$",g,s)
            if type(dd[k]) is str :
                rep = dd[k]
                thr = '0'
            elif type(dd[k]) is dict :
               rep = dd[k]["result"]
               if not isinstance(rep,list) : rep =[rep]*ret_arity
               thr = dd[k].get("ulp_thresh",0)
               if not isinstance(thr,list) : thr =[thr]*ret_arity
            else :
                rep = dd[k][0]
                thr = dd[k][1]
            r.append("  {")
            r.append(s)
##            print("rep %s"%rep)
            for i in range(0,ret_arity) :
                s1 =re.sub("\$i\$",str(i),Call)
                s1 =re.sub("\$call_param_res\$",rep[i],s1)
                s1 =re.sub("\$specific_thresh\$",thr[i],s1)
                if self.mode == 'simd' :
                    s1 =re.sub("T","vT",s1)
                r.append(s1)
            r.append("  }")
        return r

if __name__ == "__main__" :
    from pprint        import PrettyPrinter
    from unit_base_gen import Base_gen
    from unit_type_header_gen import Type_header_test_gen
##    print (__doc__)
    bg = Base_gen("exponential",'pipo','scalar')
    dl = bg.get_fct_dict_list()
    r = []
    for d in dl :
        types = bg.recover("types",d["functor"],[])
        d_unit = d["unit"]
        for typ in types :
            thg = Type_header_test_gen(bg,d,typ)
            r+=thg.get_gen_beg()
            if d_unit.get("specific_values",None) :
                svt = Specific_values_test_gen(bg,d,typ)
                r += svt. get_gen_result()
            r+=thg.get_gen_end()
    PrettyPrinter().pprint(r)

sys.path.pop(0)
sys.path.pop(0)
