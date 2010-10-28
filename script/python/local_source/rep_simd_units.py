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
import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write, exist, mkdir
from mylogging  import Mylogging
from list_utils import show
from mk_tb_txt  import create_txt
from recover_sys_toolboxes import Recover
from re_list    import sub_list

class Rep_units_simd(Functor) :
    """ insert files where needed"""
    Simd_unit = [
        "//////////////////////////////////////////////////////////////////////////////",
        "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
        "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
        "///",
        "///          Distributed under the Boost Software License, Version 1.0",
        "///                 See accompanying file LICENSE.txt or copy at",
        "///                     http://www.boost.org/LICENSE_1_0.txt",
        "//////////////////////////////////////////////////////////////////////////////",
        '#define NT2_UNIT_MODULE "nt2 predicates toolbox - unit/simd Mode"',
        "",
        "#include <nt2/toolbox/$tb_name$/include/$name$.hpp>",
        "#include <nt2/sdk/unit/tests.hpp>",
        "#include <nt2/sdk/unit/module.hpp>",
        "#include <nt2/sdk/simd/native.hpp>",
        "#include <nt2/sdk/memory/is_aligned.hpp>",
        "#include <nt2/sdk/memory/aligned_type.hpp>",
        "#include <nt2/sdk/memory/load.hpp>",
        "#include <nt2/sdk/functor/meta/call.hpp>",
        "#include <boost/type_traits/is_same.hpp>",
        "#include <nt2/include/functions/random.hpp>",
        "#include <nt2/include/functions/boolean.hpp>",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Test behavior of arithmetic components using NT2_TEST_CASE",
        "//////////////////////////////////////////////////////////////////////////////",
        "NT2_TEST_CASE_TPL($name$, NT2_SIMD_TYPES )",
        "{",
        " using nt2::$name$;",
        " using nt2::functors::$name$_; ",   
        " using nt2::load;  ",
        " using nt2::simd::native; ",
        " using nt2::meta::cardinal_of;",
        "",
        " typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;",
        " typedef native<T,ext_t>             n_t;",
        " typedef typename nt2::meta::call<$name$_(n_t)>::type call_type;",
        "",
        " NT2_TEST( (boost::is_same<call_type, n_t>::value) );  ",
        " NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];",
        " for(int j =  0;  j < 10; j++)",
        "   {",
        "     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){",
        "       data[i] = nt2::random(-10000.0, 10000.0); // good value here for $name$",
        "     }",
        "     n_t a0 = load<n_t>(&data[0],0); ",
        "     n_t v  = $name$(a0);",
        "     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)",
        "       { ",
        "	 NT2_TEST_EQUAL(nt2::boolean(v[j]), $name$(a0[j]));",
        "       }",
        "   }",
        "}"
        ]
    Insertions = {
##        "Minf<.*>"    : "#include <nt2/sdk/constant/infinites.hpp>", 

        }
    Replacement = {
##        "simd::sse_" :"tag::sse_",
    }
    def __init__(self, tb_name, style='sys') :
        Functor.__init__(self,tb_name,'modify','sys')
        self.__tb_name = tb_name
        self.__unit_simd_path = os.path.join(self.get_path_to_nt2(),'nt2/toolbox',tb_name,"unit/simd")
        self.__mk_list_simd_units()

    def __mk_list_simd_units(self) :
        self.__list_cpps = [ f for f in os.listdir(self.get_unit_simd_path()) if f[-4:]=='.cpp']
        

    def get_tb_name(self) : return self.__tb_name
    def get_list_cpps(self) : return self.__list_cpps
    def get_unit_simd_path(self) : return self.__unit_simd_path
    def ok(self,f) :   return (os.path.getsize(f) < 1024) 
            

        
    def replace(self) :
        for f in self.get_list_cpps() :
            full_f =  os.path.join(self.get_unit_simd_path(),f)
            if self.ok(full_f) :
                s = Rep_units_simd.Simd_unit
                s=sub_list("\$name\$",f[:-4],s)
                s=sub_list("\$tb_name\$",self.get_tb_name(),s)
                show(s)
                write(full_f,s,False)

if __name__ == "__main__":
    Mylogging.set_level('CRITICAL')
    i=Rep_units_simd("predicates")
#    show(i.get_list_cpps())
    i.replace()
sys.path.pop(0)
