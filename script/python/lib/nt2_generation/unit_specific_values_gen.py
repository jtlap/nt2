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
from nt2_fct_props import Nt2_fct_props
from unit_base_gen import Base_gen
sys.path.pop(0)
sys.path.pop(0)
import re


##E_dict = {
##    'scalar' :{}, 
##    'sse' :{
##       "fundamental_" : "NT2_TYPES(bool)",
##       "arithmetic_"  : "NT2_TYPES",
##       "real_"        : "NT2_REAL_TYPES",
##       "real_convert_": "NT2_REAL_CONVERTIBLE_TYPES",
##       "int_convert_" : "NT2_INT_CONVERT_TYPES", 
##       "uint_convert_": "NT2_UINT_CONVERT_TYPES",  
##       "unsigned_"    : "NT2_UNSIGNED_TYPES",
##       "unsigned_int_": "NT2_UNSIGNED_TYPES", 
##       "signed_int_"  : "NT2_INTEGRAL_SIGNED_TYPES",  
##       "integer_"     : "NT2_INTEGRAL_TYPES",  
##       "signed_"      : "NT2_SIGNED_TYPES",
##       "int64_"       : "NT2_INT_64_TYPES",
##       "int32_"       : "NT2_INT_32_TYPES",
##       "int16_"       : "NT2_INT_16_TYPES", 
##       "int8_"        : "NT2_INT_8_TYPES",
##       "groupable_"   : "NT2_GROUPABLE_TYPES",
##       "splitable_"   : "NT2_SPLITABLE_TYPES",
##       "gt_8_"        : "NT2_INT_GT8_TYPES",
##       "sintgt_8_"    : "NT2_SIGNED_INT_GT_8_TYPES",
##       "uintgt_8_"    : "NT2_UNSIGNED_INT_GT_8_TYPES",
##       "lt_64_"       : "NT2_LT64_TYPES",
##       "gt_16_"       : "NT2_GT16_TYPES",
##       "sintgt_16_"   : "NT2_SIGNED_INT_GT_16_TYPES",
##       "uintgt_16_"   : "NT2_UNSIGNED_INT_GT_16_TYPES",
##        },
##    'altivec' : {}, 
##        }

def extract(d,key_substitute,default_value,*fromkeys) :
    d1 =d
    for k in fromkeys :
        if isinstance(d1,dict) :
            d1 = d1.get(k,d1.get(key_substitute,default_value))
    return d1    

class Specific_values_test_gen(object) :
    def __init__(self, base_gen,d,typ,ret_arity,platform) :
        self.__module  = d["functor"].get('module','default')
        self._prefix = 'NT2' if self.__module == 'default' else 'NT2'
        self.bg = base_gen
        self.mode = self.bg.get_fct_mode()
        self.ret_arity = ret_arity
        self.platform = platform
        self.__gen_result = self.__create_v_tests(d,typ)
        
    def get_gen_result(self) : return  self.__gen_result
    def get_spec_value_call_tpl(self,d) :
        """ this is the call template to the test of the value
            Two main cases scalar and simd
               in simd the value passed is a splat of one scalar value
               and only the first result element is considered
               If special property of functor is predicate we know that the result is logical.
               This implies that we have to convert simd logical to bool in comparison.
               """
        if self.mode == 'simd' :
            special = extract(d,"",[""],"functor","special")[0]
            if special in ['predicate','fuzzy'] :
                spec_values_tpl = "  "+self._prefix+"_TEST_%sEQUAL($fct_name_repl$$tpl_parm$($call_param_vals$)[0]!=0, $call_param_res$%s);"
            elif special in ['reduction']:
                spec_values_tpl = "  "+self._prefix+"_TEST_%sEQUAL($fct_name_repl$$tpl_parm$($call_param_vals$), $call_param_res$%s);"
            else :
                spec_values_tpl = "  "+self._prefix+"_TEST_%sEQUAL($fct_name_repl$$tpl_parm$($call_param_vals$)[0], $call_param_res$%s);"
        else :
            spec_values_tpl = "  "+self._prefix+"_TEST_%sEQUAL($fct_name_repl$$tpl_parm$($call_param_vals$), $call_param_res$%s);"
        return spec_values_tpl

    def expand_to_list(self,typ) :
##        print("typ ->>> %s"%typ)
        return self.bg.Expansion_dict[self.platform].get(typ,typ)
    
    def __create_v_tests(self,dl,typ) :
        typs = self.expand_to_list(typ)
##        print ("=>>> %s"%typs)
##        print ("=>>> %s"%typ)
        self.__grouping_used = False
        r = []
        for t in typs :
            r+=self.__create_v_test(dl,t,typ)
            if self.__grouping_used : break;
        if dl["functor"].get("module","")=="boost" :
            r = [ re.sub("nt2::","boost::simd::",rr) for rr in r]
        return r
    
    def __create_v_test(self,dl,typ,orig_type) :
        unit_specific = extract(dl,"","",'unit',"specific_values")
        r = ["", "  // specific values tests"]
        no_ulp = extract(dl,"","False","unit","global_header","no_ulp")
        no_ulp = False if no_ulp == 'False' else no_ulp      #does we do an ulp-equality test or merely an equality test    
##        if not isinstance(unit_specific, dict) or not unit_specific.get("manual",False) :
##            return False

        if isinstance(unit_specific, dict) :
           p = unit_specific.get("prolog",False) 
           if p : r = self.__add(p,r)
        if self.ret_arity <= 1 :
            r = self.__create_values_test(dl,typ,orig_type,no_ulp,r)
##            print("ooo=========  r")
##            for rr in r : print(rr)
##            raise SystemExit
        else :
            r = self.__create_tuple_values_test(dl,typ,orig_type,no_ulp,r)            
        if isinstance(unit_specific, dict) :
            e = unit_specific.get("epilog",False) 
            if e : r = self.__add(e,r)
        return r


    def __create_values_test(self,dl,typ,orig_typ,no_ulp,r) :
        unit_specific = extract(dl,"","",'unit',"specific_values")
        print("unit_specific   %s"%unit_specific)
        ulp_str = "" if no_ulp else "ULP_"                   #string to modify the macro name accordingly
        thresh_str = "" if no_ulp else ", $specific_thresh$" # provision for the possible ulp threshold
        spec_values_tpl = self.get_spec_value_call_tpl(dl)   # template for macro call
        print("typ   %s"%typ)
        print("otype %s"%orig_typ)
        typ_values = unit_specific.get(typ,None)
        if typ_values is None:
            typ_values = extract(unit_specific,"default",None,orig_typ)
            self.__grouping_used = True
        # typ_values is the dictionnary of types for which specific values calls will be generated
        print("typ_values = %s"%typ_values)
        for k in sorted(typ_values.keys()) :
            #print("typ = %s"%typ)
            # k is here the string representation of the list of parameters f the functor
            # with only one parameter (and no commas init) it will be repeated
            #   to reach correct arity
            # else it will be taken as it is  
            s = spec_values_tpl%  (ulp_str,thresh_str)
            n = extract(unit_specific,"",self.bg.get_fct_name(),"functor","name")  
            s =re.sub("\$fct_name_repl\$",n,s)
            if k.count(',')==0 : ## one for all but no , !
                g = ', '.join([k]*int(extract(dl,"","1","functor","arity")))
            else :                 ## regular call parameters list
                g = k
            if self.mode == 'simd' :
                g =re.sub("(?<!v)T","vT",g)
                g =re.sub("vTrue","True",g)
                g =re.sub("vTwo","Two",g)
                g =re.sub("vThree","Three",g)
                g =re.sub("vTen"  ,"Ten",g)
                g =re.sub("vTwelve"  ,"Twelve",g)
                g =re.sub("vThousand","Thousand",g)
                g =re.sub("ivT\(","nt2::splat<ivT>(",g)
                g =re.sub("vT\(","nt2::splat<vT>(",g)
            s =re.sub("\$call_param_vals\$",g,s)
            g = dl["functor"].get("tpl","")

            s =re.sub("\$tpl_parm\$",g,s)
            def get_rep_thr(dd) :
                if isinstance(dd[k], str ) :
                    rep = dd[k]
                    thr = '0'
                elif isinstance(dd[k], dict ) :
                    rep = dd[k]["result"]
                    thr = dd[k].get("ulp_thresh",'1.0')
                else :
                    rep = dd[k][0]
                    thr = dd[k][1]
                if self.mode == 'simd' :
                    rep =re.sub("r_t","sr_t",rep)
                return (rep,thr)
            rep, thr =get_rep_thr(typ_values)
            s =re.sub("\$call_param_res\$",rep,s)
            s =re.sub("\$specific_thresh\$",thr,s)
            r.append(s)
        return r    

    def __create_tuple_values_test(self,dl,typ,orig_typ,no_ulp,r) :
        d = extract(dl,"","",'unit',"specific_values")
        if no_ulp :
            Call = "    "+self._prefix+"_TEST_EQUAL( boost::fusion::get<$i$>(res), $call_param_res$);"
        else :
            Call = "    "+self._prefix+"_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<$i$>(res)$simd$, $call_param_res$$simd$, $specific_thresh$);"
            
        Results = "    r_t res = $fct_name$$tpl_parm$($call_param_vals$);"
        dd = d.get(typ,d.get("default",None))
        if dd is None : dd = d.get(orig_typ,d.get("default",None))
        r = ["",
             "  // specific values tests",]
        for i in range(self.ret_arity) :
            r.append("  typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,%s>::type>::type r_t%s;"%(str(i),str(i)))

        for k in sorted(dd.keys()) :
            s = Results
            s =re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
            if k.count(',')==0 : ## one for all but no , !
                g = ', '.join([k]*int(dl["functor"]["arity"]))
            else :                 ## regular call parameters list
                g = k
            if self.mode == 'simd' :
                g =re.sub("(?<!v)T","vT",g)
                g =re.sub("vTrue","True",g)
                g =re.sub("vTwo","Two",g)
                g =re.sub("vTen"  ,"Ten",g)
                g =re.sub("vTwelve"  ,"Twelve",g)
                g =re.sub("vThree","Three",g)
                g =re.sub("ivT\(","nt2::splat<ivT>(",g)
                g =re.sub("vT\(","nt2::splat<vT>(",g)
            s =re.sub("\$call_param_vals\$",g,s)
            g = dl["functor"].get("tpl","")

            s =re.sub("\$tpl_parm\$",g,s)
            if  isinstance(dd[k], str ) :
                rep = dd[k]
                thr = '0'
            elif isinstance(dd[k], dict ) :
               rep = dd[k]["result"]
               if not isinstance(rep,list) : rep =[rep]*self.ret_arity
               thr = dd[k].get("ulp_thresh",0)
               if not isinstance(thr,list) : thr =[thr]*self.ret_arity
            else :
                rep = dd[k][0]
                thr = dd[k][1]
            r.append("  {")
            r.append(s)
            print("rep %s"%rep)
            for i in range(0,self.ret_arity) :
                s1 =re.sub("\$i\$",str(i),Call)
                s1 =re.sub("\$call_param_res\$",rep[i],s1)
                s1 =re.sub("\$specific_thresh\$",thr[i],s1)
                if self.mode == "simd" :
                    s1 = re.sub("\$simd\$","[0]",s1)
                else :
                    s1 = re.sub("\$simd\$","",s1)
                        
                r.append(s1)
            r.append("  }")
        return r    

    def __add(s,r) :
        if isinstance(s, str) :
            return r.append(s)
        elif  isinstance(s, list ) :
            return r.extend(s)
        return r
    
if __name__ == "__main__" :
    from pprint        import PrettyPrinter
    from unit_base_gen import Base_gen
    from unit_type_header_gen import Type_header_test_gen
##    print (__doc__)
    bg = Base_gen("arithmetic",'abs','scalar')
    dl = bg.get_fct_dict_list()
    r = []
    for d in dl :
        ret_arity = int(extract(d,"","","functor","ret_arity"))
        types = bg.recover("types",d["functor"],[])
        d_unit = d["unit"]
        for typ in types :
            thg = Type_header_test_gen(bg,d,typ,0)
            r+=thg.get_gen_beg()
            if d_unit.get("specific_values",None) :
                svt = Specific_values_test_gen(bg,d,typ,ret_arity,'scalar')
                r += svt. get_gen_result()
            r+=thg.get_gen_end()
    PrettyPrinter().pprint(r)

