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


"""base for generation of a functor random unit tests
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

class Random_tuple_test_gen(Base_gen) :
    Random_test_body = [
        "  // random comparison with other impl or formula for tuples",
        "  static const uint32_t NR = $nb_rand$;",
        "  {",
        "    $buffers_creation$ ",
        "    for (int j =0; j < NR; ++j )",
        "      {",
        '        std::cout << "for param$plural$ "',
        "                  $show_params$",
        "                  << std::endl;",
        "        $calls$",
        "     }",
        "   }",
        ]
    def __init__(self, base_gen,d,typ) :
        self.bg   = base_gen
        self.__gen_result = self.__create_unit_txt(d,typ)

    def get_gen_result(self) : return  self.__gen_result

    def __create_unit_txt(self,dl,typ) :
        d = dl['unit']["random_tuple_test"]
        r = self.bg.create_unit_txt_part( Random_tuple_test_gen.Random_test_body,self.__prepare,dl,typ)
        return r
    
    def __prepare(self,s,typ,d) :
        df = d["functor"]
        arity = df["arity"]
        s=re.sub("\$nb_rand\$","100",s)
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
        s=re.sub("\$plural\$", "s" if arity>1 else "",s)
        du = d["unit"]
        ret_arity = int(d["functor"].get("ret_arity","0"))
        dur= du["random_tuple_test"]  
        dura = dur["alternate_call"]
        m = re.match("( *)\$buffers_creation\$.*",s)
        if m :
            beg = m.groups()[0]
            actual_ranges = du["ranges"].get(typ,du["ranges"]["default"])
            s = []
            tpdefs = d["functor"].get("type_defs",None)
            if tpdefs is not None :
                for l in tpdefs : s.append( beg+l) 
            for i in xrange(0, arity) :
                j = min(i,len(actual_ranges)-1)
                rg0 =  actual_ranges[j][0]
                rg1 =  actual_ranges[j][1]
                s.append( beg+("NT2_CREATE_BUF(tab_a%d,"%i)+ self.__get_typ(i,df)+(", 100, %s, %s);" %(rg0,rg1)))
            return s
        m = re.match("( *)\$show_params\$.*",s)
        if m :
            beg = m.groups()[0]
            s= [ beg+'<< "%(p)s a%(i)d = "<< u_t(a%(i)d = tab_a%(i)d[j])' %{'i':i,'p' : (',' if i else ' ')}
                 for i in xrange(0, arity) ]
            return s
        m = re.match(".*\$call_param\$.*",s)
        if m :
            g= ','.join([ "a%d" % i for i in xrange(0, arity) ])
            s=re.sub("\$call_param\$",g,s)
            return s
        m = re.match("( *)\$calls\$.*",s)
        if m :
            call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
            beg = m.groups()[0]
            if ret_arity :
                s = [beg + 'r_t r = nt2::'+self.bg.get_fct_name()+'('+call_param+");"]

                tpl = "NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<$index$>(r), $alternate_call$,$ulp_thresh$);"
                th = dur["ulp_thresh"]
                if type(th) is str :  th = [th]*ret_arity
                for i in xrange(0, ret_arity) :
                    l = re.sub('\$index\$',str(i),tpl)
                    l = re.sub('\$alternate_call\$',dura.get(typ,dura["default"])[i],l)
                    l = re.sub('\$ulp_thresh\$',th[i],l)
                    s.append(beg+l)
            else :
                s = beg+"NT2_TEST_ULP_EQUAL( nt2::$fct_name$($call_param$),$alternate_call$,$ulp_thresh$);"
                s = re.sub('\$ulp_thresh\$',dur.get("ulp_thresh","0"),s)
                s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
                s=re.sub("\$alternate_call\$" ,dura.get(typ,dura["default"]),s)
                s=re.sub("\$call_param\$",call_param,s)
        return s
    
    def __get_typ(self,i,d) :
        dd = d.get("call_types",None)
        if dd is None :
            return "T"
        elif type(dd) is str :
            return dd
        else :
            return dd[i]


if __name__ == "__main__" :
    from pprint        import PrettyPrinter
    from unit_base_gen import Base_gen
    from unit_type_header_gen import Type_header_test_gen
    from unit_specific_values_gen import Specific_values_test_gen
    print __doc__
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
            if d_unit.get("random_tuple_test",None) :
                rtg = Random_tuple_test_gen(bg,d,typ)
                r += rtg. get_gen_result()
            r+=thg.get_gen_end()
    PrettyPrinter().pprint(r)

sys.path.pop(0)
sys.path.pop(0)
