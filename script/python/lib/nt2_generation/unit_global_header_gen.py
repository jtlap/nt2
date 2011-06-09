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
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from unit_base_gen import Base_gen
sys.path.pop(0)

import re
import datetime

class Global_header_gen() :
    Header_template = [
            "//////////////////////////////////////////////////////////////////////////////",
            "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
            "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
            "///",
            "///          Distributed under the Boost Software License, Version 1.0",
            "///                 See accompanying file LICENSE.txt or copy at",
            "///                     http://www.boost.org/LICENSE_1_0.txt",
            "//////////////////////////////////////////////////////////////////////////////",
            '#define NT2_$kind$_MODULE "nt2 $tb_name$ toolbox - $fct_name$/$fct_mode$ Mode"',
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// $kind$ test behavior of $tb_name$ components in $fct_mode$ mode",
            "//////////////////////////////////////////////////////////////////////////////",
            ""
            "$first_stamp$",
            "$notes$",
            "#include <nt2/toolbox/$tb_name$/include/$fct_name$.hpp>",
            ]
    Default_template =  [
            "#include <boost/type_traits/is_same.hpp>",
            "#include <nt2/sdk/functor/meta/call.hpp>",
            "#include <nt2/sdk/unit/$no_ulp$tests.hpp>",
            "#include <nt2/sdk/unit/module.hpp>",
            "#include <nt2/sdk/memory/buffer.hpp>",
            "#include <nt2/include/constants/real.hpp>",
            "#include <nt2/include/constants/infinites.hpp>",
            ]
    
    Template = {
        "scalar" :
        [
            ],
        "simd" :
        [
            "#include <nt2/sdk/memory/is_aligned.hpp>",
            "#include <nt2/sdk/memory/aligned_type.hpp>",
            "#include <nt2/include/functions/load.hpp>",           
            "//#include <nt2/include/functions/max.hpp>",
            "#include <nt2/toolbox/$tb_name$/include/$fct_name$.hpp>",
            ]
        }
    def __init__(self, base_gen,part) :
        self.part = part
        self.bg   = base_gen
        self.mode = self.bg.get_fct_mode()
        self.__gen_result = self.__create_unit_txt()
        
    def get_gen_result(self) :
        return  self.__gen_result

    def add_header(self,dl) :
        r = self.bg.create_unit_txt_part( Global_header_gen.Header_template,
                                          self.__prepare,d=dl[0]['unit']['global_header'])
        for d in dl :
             no_ulp = d['functor'].get('no_ulp',False)
             if not no_ulp :
                 r.append("#include <nt2/include/functions/ulpdist.hpp>")
                 return r
        return r
    
    def add_includes(self,r,dl) :
        include_src = 'included' if self.mode == 'scalar' else "simd_included"
        tuple_included = False
        default_includes = True
        for d in dl :
            dug = d['unit']['global_header']
            df  = d['functor']
            if dug.get("no_default_includes",False) : default_includes = False
            includes = dug.get("all_cases_includes",False)
            if includes :
                r.extend(includes)
            if not tuple_included and int(df.get("ret_arity","1")) > 1 :
                tuple_included = True
                r.append('#include <boost/fusion/tuple.hpp>')
            includes = dug.get(include_src,False);
            if includes :
                if isinstance(includes,str ) :
                    r.append(includes)
                if isinstance(includes,list ) :
                    r.extend(includes)
                elif isinstance(includes,dict ) :
                    includes = includes.get(self.part,False)
                    if includes :
                        if isinstance(includes,str ) :
                            r.append(includes)
                        if isinstance(includes,list ) :
                            r.extend(includes)
            r.append('')
            if default_includes : #uses default once
                r1 = self.bg.create_unit_txt_part( Global_header_gen.Default_template,self.__prepare,d=d)
                r.extend(r1)
            r.append('')
        return r    

        
    def __create_unit_txt(self) :
        dl = self.bg.get_fct_dict_list()
        r = self.add_header(dl)
        r = self.add_includes(r,dl)
        return r

    def __prepare(self,s,typ,d,i=None) :
        s=re.sub("\$kind\$",self.part.upper(),s)
        s=re.sub("\$fct_mode\$",self.bg.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.bg.get_tb_name(),s)
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
##        st = d.get("stamp","")
##        st = re.sub("\d+/\d+/\d+",datetime.datetime.now().strftime("%d/%m/%Y"),st)
##        s=re.sub("\$stamp\$", '/// '+st,s)
        fs = d.get("first_stamp","")
        fs = re.sub("modified","created",fs)
        s=re.sub("\$first_stamp\$", '/// '+fs,s)
        s=re.sub("\$no_ulp\$", "" if d.get("no_ulp",False) != True else "no_ulp_",s)
        m = re.search('\$notes\$',s)
        if m :
            s = []
            beg = '/// '
            n = d.get("notes",[])
            for l in n :
                ll = l.split('\n')
                for lll in ll :
                    s.append(beg + lll.lstrip())
        return s

if __name__ == "__main__" :
    print __doc__
    from pprint   import PrettyPrinter
    bg = Base_gen("exponential",'exp','scalar')
    ghg = Global_header_gen(bg,'cover')
    PrettyPrinter().pprint(ghg.get_gen_result())
