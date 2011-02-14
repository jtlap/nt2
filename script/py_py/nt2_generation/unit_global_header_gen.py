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
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
import re
from unit_base_gen import Base_gen

class Global_header_gen() :
    Template = [
        "//////////////////////////////////////////////////////////////////////////////",
        "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
        "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
        "///",
        "///          Distributed under the Boost Software License, Version 1.0",
        "///                 See accompanying file LICENSE.txt or copy at",
        "///                     http://www.boost.org/LICENSE_1_0.txt",
        "//////////////////////////////////////////////////////////////////////////////",
        '#define NT2_UNIT_MODULE "nt2 $tb_name$ toolbox - $fct_name$/$fct_mode$ Mode"',
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Test behavior of $tb_name$ components in $fct_mode$ mode",
        "//////////////////////////////////////////////////////////////////////////////",
        ""
        "$first_stamp$",
        "$stamp$",
        "$notes$",
        "#include <boost/type_traits/is_same.hpp>",
        "#include <nt2/sdk/functor/meta/call.hpp>",
        "#include <nt2/sdk/unit/tests.hpp>",
        "#include <nt2/sdk/unit/module.hpp>",
        "#include <nt2/sdk/memory/buffer.hpp>",
        "#include <nt2/sdk/constant/real.hpp>",
        "#include <nt2/sdk/constant/infinites.hpp>",
        "#include <nt2/toolbox/$tb_name$/include/$fct_name$.hpp>",
       ]
    def __init__(self, base_gen) :
        self.bg   = base_gen
        self.__gen_result = self.__create_unit_txt()

    def get_gen_result(self) : return  self.__gen_result
    
    def __create_unit_txt(self) :
        dl = self.bg.get_fct_dict_list()
        d = dl[0]['unit']['global_header']
        r = self.bg.create_unit_txt_part( Global_header_gen.Template,self.__prepare,d=d)
        for dd in dl :
            d = dd['unit']['global_header']
            l = d['included']
            if len(l) :
                r.append("// specific includes for arity "+ str(dd['functor']['arity'])+" tests")
                r += d['included']           
        return r

    def __prepare(self,s,typ,d) :
        s=re.sub("\$fct_mode\$",self.bg.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.bg.get_tb_name(),s)
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
        s=re.sub("\$stamp\$", '/// '+d.get("stamp",""),s)
        s=re.sub("\$first_stamp\$", '/// '+d.get("first_stamp",""),s)
        m = re.search('\$notes\$',s)
        if m :
            s = []
            beg = '/// '
            n = d.get("notes",[])
            for l in n : s.append(beg + l)
        return s

if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    bg = Base_gen("exponential",'pipo','scalar')
    ghg = Global_header_gen(bg)
    PrettyPrinter().pprint(ghg.get_gen_result())
sys.path.pop(0)
sys.path.pop(0)
