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
            '#define NT2_UNIT_MODULE "nt2 $tb_name$ toolbox - $fct_name$/$fct_mode$ Mode"',
            "",
            "//////////////////////////////////////////////////////////////////////////////",
            "// $kind$ test behavior of $tb_name$ components in $fct_mode$ mode",
            "//////////////////////////////////////////////////////////////////////////////",
            ""
            "$first_stamp$",
            "$stamp$",
            "$notes$",
            ]
    Default_template = {
        'default' : [
            "#include <boost/type_traits/is_same.hpp>",
            "#include <nt2/sdk/functor/meta/call.hpp>",
            "#include <nt2/sdk/meta/as_integer.hpp>",
            "#include <nt2/sdk/meta/as_floating.hpp>",
            "#include <nt2/sdk/meta/as_signed.hpp>",
            "#include <nt2/sdk/meta/upgrade.hpp>",
            "#include <nt2/sdk/meta/downgrade.hpp>",
            "#include <nt2/sdk/meta/scalar_of.hpp>",
            "#include <nt2/sdk/unit/$no_ulp$tests.hpp>",
            "#include <nt2/sdk/unit/module.hpp>",
            "#include <nt2/sdk/memory/buffer.hpp>",
            "#include <nt2/toolbox/constant/constant.hpp>",
            "#include <boost/dispatch/details/ignore_unused.hpp>"
            ],
        'boost' : [
            "#include <boost/type_traits/is_same.hpp>",
            "#include <boost/dispatch/functor/meta/call.hpp>",
            "#include <nt2/sdk/unit/$no_ulp$tests.hpp>",
            "#include <nt2/sdk/unit/module.hpp>",
            "#include <boost/simd/sdk/memory/buffer.hpp>",
            "#include <boost/simd/toolbox/constant/constant.hpp>",
            "#include <boost/dispatch/details/ignore_unused.hpp>"
            ]
        }
    
    Simd_template =  {
        'default' : [
            "#include <nt2/sdk/meta/cardinal_of.hpp>",
            "#include <nt2/include/functions/splat.hpp>",
            "#include <nt2/sdk/memory/is_aligned.hpp>",
            "#include <nt2/sdk/memory/aligned_type.hpp>",
            "#include <nt2/include/functions/load.hpp>",
            "#include <nt2/toolbox/constant/constant.hpp>",
            "#include <boost/dispatch/details/ignore_unused.hpp>",
            ],
        'boost' : [
            "#include <boost/simd/sdk/memory/is_aligned.hpp>",
            "#include <boost/simd/sdk/memory/aligned_type.hpp>",
            "#include <boost/simd/include/functions/load.hpp>",           
            "#include <boost/simd/toolbox/constant/constant.hpp>",
            "#include <boost/dispatch/details/ignore_unused.hpp>"
            ]
        }
    Cover_Template = {
        'default' : "#include <nt2/include/functions/max.hpp>",         
        'boost'   : "#include <boost/simd/include/functions/max.hpp>",
        }
    No_ulp_Template = {
        'default' : "#include <nt2/include/functions/ulpdist.hpp>",         
        'boost'   : "#include <boost/simd/include/functions/ulpdist.hpp>", 
        }
    Default_dug = {
        'first_stamp' : 'modified by ??? the ???',
        'no_default_includes' : False,  
        'notes' : ["this is a default generation"],
        }
    
    def __init__(self,base_gen,part,stampit=False) :
        self.stampit = stampit
        self.part = part
        self.bg   = base_gen
        self.mode = self.bg.get_fct_mode()
        self.__gen_result = self.__create_unit_txt()
        
    def get_gen_result(self) :
        return  self.__gen_result

    def add_header(self,dl) :
        du = dl[0].get('unit',False)
        if isinstance(du, dict ) :
            dug =  du.get('global_header',Global_header_gen.Default_dug)
        else :
            dug = Global_header_gen.Default_dug
        if dug :
            r = self.bg.create_unit_txt_part( Global_header_gen.Header_template,
                                              self.__prepare,d=dug)
            if os.path.exists(self.bg.get_fct_doc_path()) :
                pos = 1 if self.__module == 'default' else 2
                l = os.path.join(self.bg.demangle(self.bg.get_tb_name(),'toolbox',pos),"include/functions",self.bg.get_fct_name()+".hpp")
                r.append("#include <"+l+">")
##                r.append("#include <nt2/toolbox/"+bg.demangle(self.bg.get_tb_name())+"/include/"+self.bg.get_fct_name()+".hpp>")
##                print(r[-1])
            for d in dl :
                du =  d.get('unit',{})
                dg =  du.get('global_header',False)
                no_ulp =  dg.get('no_ulp',False) if dg else True
                if not no_ulp :
                    r.append(Global_header_gen.No_ulp_Template[self.__module])
                    if self.part == "cover" :
                        r.append(Global_header_gen.Cover_Template[self.__module])
                    return r
        return r
    
    def add_includes(self,r,dl) :
##        print ("part = %s"%self.part)
        include_src = ['included']
        if self.mode == 'simd':
            include_src.extend(['simd_included'])
        else :   
            include_src.extend(['scalar_included'])
        if self.part == 'cover':
            include_src.extend(['cover_included'])
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
            if isinstance(include_src,str ) : include_src = [include_src]
            print("*********** %s"%include_src)
            for incl in include_src :
                includes = dug.get(incl,False);
                print("--%s=========== %s"%(incl,includes))
                if includes :
                    print("--%s=========== %s"%(incl,includes))
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
                default_includes = False
                r1 = self.bg.create_unit_txt_part( Global_header_gen.Default_template[self.__module],self.__prepare,d=d)
                r.extend(r1)
                if self.mode == "simd" : r.extend(Global_header_gen.Simd_template[self.__module])
            r.append('')
        def is_include(st) :
            st =st.lstrip()
            return len(st)>5 and( (st[0:6] =="#inclu") or (st[0:6] =="extern"))
        def uniquer(seq):
            seen = {}
            result = []
            for item in seq:
                if (item in seen) and is_include(item): continue
                seen[item] = 1
                result.append(item)
            return result
        if len(dl)>1 : r=uniquer(r)    
        return r    

        
    def __create_unit_txt(self) :
        dl = self.bg.get_fct_dict_list()
        if isinstance(dl,dict ) : dl = [dl]
##        print (dl)
        self.__module = dl[0].get('functor',False).get("module",'default')
        if self.__module != 'boost' : self.__module = 'default'
        r = self.add_header(dl)
        r = self.add_includes(r,dl)
        return r

    def __prepare(self,s,typ,d,i=None) :
        s=re.sub("\$kind\$",self.part,s)
        s=re.sub("\$fct_mode\$",self.bg.get_fct_mode(),s)
        s=re.sub("\$tb_name\$",self.bg.get_tb_name(),s)
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
        if self.stampit :
            st = d.get("stamp","")
            st = re.sub("\d+/\d+/\d+",datetime.datetime.now().strftime("%d/%m/%Y"),st)
            s=re.sub("\$stamp\$", '/// '+st,s)
        else :
            s=re.sub("\$stamp\$", '/// ',s)
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
