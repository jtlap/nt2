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


"""unit test generation for a functor
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
import shutil
from display_utils import show
from files_utils   import write, exist
from nt2_toolbox_infos import Toolbox_infos
from nt2_tb_functors_infos import Fctor_infos
from nt2_types_tags import range_of_type_limits


class Meta_gen_fct_unit( Fctor_infos) :
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
    Global_header = [
        "//////////////////////////////////////////////////////////////////////////////",
        "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
        "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
        "///",
        "///          Distributed under the Boost Software License, Version 1.0",
        "///                 See accompanying file LICENSE.txt or copy at",
        "///                     http://www.boost.org/LICENSE_1_0.txt",
        "//////////////////////////////////////////////////////////////////////////////",
        '#define NT2_UNIT_MODULE "nt2 $tb_name$ toolbox - $fct_name$/$mode$ Mode"',
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Test behavior of $tb_name$ components in $mode$ ",
        "//////////////////////////////////////////////////////////////////////////////",
        ""
        "#include <nt2/sdk/functor/meta/call.hpp>",
        "#include <boost/type_traits/is_same.hpp>",
        "#include <nt2/toolbox/$tb_name$/include/$fct_name$.hpp>",
        "#include <nt2/sdk/unit/tests.hpp>",
        "#include <nt2/sdk/unit/module.hpp>",
        "#include <nt2/sdk/memory/buffer.hpp>",
        "#include <nt2/sdk/constant/real.hpp>",
        "#include <nt2/sdk/constant/infinites.hpp>"
       ]
    Type_Header   = [
        "",
        "NT2_TEST_CASE_TPL ( $fct_name$_$type$_$arity$,  $macro_types$)",
        "{",
        "  using nt2::$fct_name$;",
        "  using nt2::$tb_style_base$tag::$fct_name$_;",
        "  $type_defs$",
        "  typedef typename nt2::meta::call<$fct_name$_($arity_type$)>::type r_t;",
        "  typedef typename nt2::meta::upgrade<T>::type u_t;",
        "  typedef $rturn$ wished_r_t;",
        ]
    Type_Footer   = [ "} // end of test for $type$"]
    
    Type_conformity_test = [
        "",
        "  // return type conformity test ",
        "  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );",
        "  std::cout << std::endl; ",
        "",
        ]
    Random_test_body = [
        "  // random comparison with other impl or formula ",
        "  static const uint32_t NR = $nb_rand$;",
        "  {",
        "    $buffers_creation$ ",
        "    for (int j =0; j < NR; ++j )",
        "      {",
        '        std::cout << "for param$plural$ "',
        "                  $show_params$",
        "                  << std::endl;", 
        "        NT2_TEST_ULP_EQUAL( nt2::$fct_name$($call_param$), $against$,$ulp_thresh$);",
        "     }",
        "   }",
        ]
    Random_tuple_test_body = [
        "  // random comparison with other impl or formula ",
        "  static const uint32_t NR = $nb_rand$;",
        "  {",
        "    $buffers_creation$ ",
        "    for (int j =0; j < NR; ++j )",
        "      {",
        '        std::cout << "for param$plural$ "',
        "                  $show_params$",
        "                  << std::endl;",
        "        r_t r = nt2::$fct_name$($call_param$);",
        "        NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<0>(r), $tcal0$,$ulp_thresh$);",
        "        NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<1>(r), $tcal1$,$ulp_thresh$);",
        "     }",
        "   }",
        ]
    Verif_test_body = [
        "  // relations verifications",
        "  static const uint32_t NT = $nb_verif$;",
        "  {",
        "    $buffers_creation$ ",
        "    for (int j =0; j < NT; ++j )",
        "      {",
        '        std::cout << "for param$plural$ "',
        "                  $show_params$",
        "                  << std::endl;", 
        "        NT2_TEST_ULP_EQUAL( $verif$,$verva$,$verth$);",
        "     }",
        "   }",
        ]
    
    Spec_values_test_tpl = "  NT2_TEST_ULP_EQUAL(  $fct_name$($call_param_vals$), $call_param_res$, $ulp_thres2$);"

    
    def __init__(self, tb_name, fct_name) :
        Fctor_infos.__init__(self,tb_name, fct_name)

    def get_fct_unit_path(self,mode)  :
        return os.path.join(self.tbi.get_tb_path(),'unit',mode,self.get_fct_name()+'.cpp')
    
    def create_unit_txt(self) :
        dl = self.get_fct_dict()
        if type(dl) is dict : dl = [dl]
        elif not (type(dl) is list ) :
           print "no dictionary available for %s" % self.get_fct_name()
        r = self.__create_unit_txt_part(Meta_gen_fct_unit.Global_header,dl[0])
        for d in dl :
            r+= self.supplemental_includes(d)
        for d in dl :
            types = d["types"]
            for typ in types :
                r += self.__create_unit_txt_part(Meta_gen_fct_unit.Type_Header,d,typ)
                if d.get("specv",None) is not None :
                    r+= self.__create_values_test(Meta_gen_fct_unit.Spec_values_test_tpl,d,typ)
                r += Meta_gen_fct_unit.Type_conformity_test
                if self.__call(typ,d) is not None :
                    r += self.__create_unit_txt_part(Meta_gen_fct_unit.Random_test_body,d,typ)
                if d.get("tuple",None) is not None :
                    r += self.__create_unit_txt_part(Meta_gen_fct_unit.Random_tuple_test_body,d,typ)
                if self.__verif(typ,d) is not None :
                    r += self.__create_unit_txt_part(Meta_gen_fct_unit.Verif_test_body,d,typ)
                r += self.__create_unit_txt_part(Meta_gen_fct_unit.Type_Footer,d,typ)
        return r

    def supplemental_includes(self,d) :
         return d.get("incld",[])
         
    def show_unit_txt(self) :
       show(self.create_unit_txt())

    def write_unit_txt(self,types=None) :
        p = self.get_fct_unit_path("scalar")
        if exist(p) :
            bak = re.sub('.cpp','.cpp.bak',p)
            shutil.copy(p,bak)
        write(p,self.create_unit_txt(),False)
            
    def __create_values_test(self,tpl,d1,typ) :
        d = d1["specv"]
        if typ in d.keys() :
           dd = d[typ]
        else :
##            print typ
            dd = d["default"]   
#        dd = d[typ] if typ in d.keys()  else d["default"]
        r = ["", "  // specific values tests"]
        for k in sorted(dd.keys()) :
            s = Meta_gen_fct_unit.Spec_values_test_tpl
            s =re.sub("\$fct_name\$",self.get_fct_name(),s)
            if k.count(',')==0 :
                g = ', '.join([k]*d1["arity"])
            else :
                g = k
            s =re.sub("\$call_param_vals\$",g,s)
            if type(dd[k]) is str :
                rep = dd[k]
                thr = '0'
            else :
                rep = dd[k][0]
                thr = dd[k][1]
            s =re.sub("\$call_param_res\$",rep,s)
            s =re.sub("\$ulp_thres2\$",thr,s)
            r.append(s)
        return r    
          
        
    def __create_unit_txt_part(self,tpl,d,typ="") :
        r = []
        for s in tpl :
            if "$" in s :
                r += self.prepare(s,typ,d)
            else :
                r.append(s)
        return r

    def get_ranges(self,d,typ)  :
        if typ in d.keys() :
            return d[typ]
        else :
            print typ
            return d["default"]

    def __macro(self,typ) :
        if typ in Meta_gen_fct_unit.Macros_dict.keys() :
            return Meta_gen_fct_unit.Macros_dict[typ]
        elif typ[-2:] =="_t" :
            return "(nt2::"+typ+")"
        else :
            return "("+typ+")"
        
    def __rturn(self,typ,d) :
        if typ in d :
            return d[typ]
        else :
            return d["default"]
        
    def __ulp_threshold(self,typ,d) :
        if typ in d :
            return d[typ]
        else :
            return "0"
    def __call(self,typ,d) :
        dd = d["tcall"]
        if dd is None :
            return None
        elif type(dd) is str :
            return dd
        else :
            return dd.get(typ, dd.get("default", None ))
        
    def __verif(self,typ,d) :
        dd =d.get("verif",None)
        if dd is None :
            return None
        elif type(dd) is str :
            return dd
        else :
            return dd.get(typ, dd.get("default", None ))

    def __verva(self,typ,d) :
        dd = d.get("verva",None)
        if dd is None :
            return None
        elif type(dd) is str :
            return dd
        else :
            return dd.get(typ, dd.get("default", None ))

    def __recover(self,st,typ,d,extra_def=None) :
        dd = d.get(st, None)
        if dd is None :
            return extra_def
        elif type(dd) is str :
            return dd
        elif dd is  None :
            return None
        else :
#                return dd.get(typ, dd.get("default", None ))
            return None

    def __get_typ(self,i,d) :
        dd = d.get("buftp",None)
        if dd is None :
            return "T"
        elif type(dd) is str :
            return dd
        else :
            return dd[i]

    def __get_arity_types(self,d) :
        dd = d.get("buftp",None)
        if dd is None :
            return ','.join(["T"]*d["arity"])
        else :
            return ','.join(dd)


    def prepare(self,s,typ,d) :
        style = self.get_tb_style()
        tb_style_base = "" if style =="sys" else self.get_tb_name()+'::'
        if re.search("\$tb_style_base\$.*",s) :
            s=re.sub("\$tb_style_base\$",tb_style_base,s)
        
#        d = self.get_fct_dict()
        if re.search("\$verif\$.*",s) :
            s=re.sub("\$verif\$",self.__recover("verif",typ,d),s)
        if re.search("\$verva\$.*",s) :
            s=re.sub("\$verva\$",self.__recover("verva",typ,d),s)    
        if re.search("\$verth\$.*",s) :
            s=re.sub("\$verth\$",self.__recover("verth",typ,d),s)    
        if re.search("\$tcal0\$.*",s) :
            s=re.sub("\$tcal0\$",self.__recover("tcal0",typ,d),s)    
        if re.search("\$tcal1\$.*",s) :
            s=re.sub("\$tcal1\$",self.__recover("tcal1",typ,d),s)    
        s=re.sub("\$ulp_thresh\$",self.__ulp_threshold(typ,d.get("ulpth",{})),s)
        s=re.sub("\$plural\$", "s" if d["arity"]>1 else "",s)
        s=re.sub("\$rturn\$", self.__rturn(typ,d["rturn"]),s)
        s=re.sub("\$arity_type\$", self.__get_arity_types(d),s)
        s=re.sub("\$macro_types\$",self.__macro(typ),s)
        s=re.sub("\$mode\$",self.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.tbi.get_tb_name(),s)
        s=re.sub("\$fct_name\$",self.get_fct_name(),s)
        s=re.sub("\$nb_rand\$","100",s)
        s=re.sub("\$nb_verif\$","100",s)
        s=re.sub("\$type\$"    ,typ,s)
        s=re.sub("\$arity\$",str(d["arity"]),s)
        g = self.__call(typ,d)
        s=re.sub("\$against\$" ,"" if g is None else g,s)
        m = re.match("( *)\$show_params\$.*",s)
        if m :
            beg = m.groups()[0]
            s= [ beg+'<< "%(p)s a%(i)d = "<< u_t(a%(i)d = tab_a%(i)d[j])' %{'i':i,'p' : (',' if i else ' ')}
                 for i in xrange(0, d["arity"]) ]
            return s
        m = re.match("( *)\$type_defs\$.*",s)
        if m :
            beg = m.groups()[0]        
            s = []
            if d.get("tpdef",None) is not None :
                for l in d.get("tpdef",None) :
                    s.append( beg+l) 
            return s
        m = re.match("( *)\$buffers_creation\$.*",s)
        if m :
            beg = m.groups()[0]
            actual_ranges = self.get_ranges(d["rnges"],typ)
            s = []
            if d.get("tpdef",None) is not None :
                for l in d.get("tpdef",None) :
                    s.append( beg+l) 
            for i in xrange(0, d["arity"]) :
                rg0 = "nt2::Valmin<T>()" if actual_ranges[i][0]=="-inf" else actual_ranges[i][0]
                rg1 = "nt2::Valmax<T>()" if actual_ranges[i][1]=="inf"  else actual_ranges[i][1]
                s.append( beg+("NT2_CREATE_BUF(tab_a%d,"%i)+ self.__get_typ(i,d)+(", 100, %s, %s);" %(rg0,rg1)))
            return s
        m = re.match(".*\$call_param\$.*",s)
        if m :
            g= ','.join([ "a%d" % i
                 for i in xrange(0, d["arity"]) ])
            s=re.sub("\$call_param\$",g,s)
            return [s]
        return [s]



if __name__ == "__main__" :
    print __doc__
    ###########  Ce n'est pas le bon !
##    mgfu = Meta_gen_fct_unit("exponential","exp")
##    mgfu.show_unit_txt()
##    mgfu.write_unit_txt()
sys.path.pop(0)
sys.path.pop(0)
