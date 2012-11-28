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
from nt2_fct_props import Nt2_fct_props
from unit_base_gen import Base_gen
sys.path.pop(0)
sys.path.pop(0)

import re
from pprint        import PrettyPrinter

class Random_verif_test_gen(Base_gen) :
    Random_test_body = {
        "scalar" :
        [
            "  {",
            "    $buffers_creation$ ",
            "    for(nt2::uint32_t j =0; j < NR; ++j )",
            "      {",
            '        std::cout << "for param$plural$ "',
            "                  $show_params$",
            "                  << std::endl;",
            "        $calls$",
            "     }",
            '     $max$',
            "   }",
            ],
        "simd" :
        [
            "  {",
            "    $buffers_creation$ ",
            "    for(nt2::uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)",
            "      {",
            "        $loads$",
            "        $calls$",
            "      }",
            '    $max$',
            "  }",
            ],
        }
    def __init__(self, base_gen,d,typ,platform) :
        self.bg   = base_gen
        self.mode = self.bg.get_fct_mode()
        self.platform = platform
        self.__gen_result = self.__create_unit_txts(d,typ)

    def get_gen_result(self) : return  self.__gen_result

    def __create_unit_txts(self,dl,orig_typ) :
        r = []
        ####        ctyp = typ if self.mode == "scalar" else self.convert(typ,dl)
        typs = self.expand_to_list(orig_typ)
        self.__grouping_used = False
##         print("oooooooo1 %s"%orig_typ)
##         print("oooooooo2 %s"%typs)
##        if len(typs) :  r = self.__create_unit_txt(dl,typs[0],typ)
        for t in typs :
            r += self.__create_unit_txt(dl,t,orig_typ)
            if self.__grouping_used : break;
        return r

    def __create_unit_txt(self,dl,typ,orig_typ) :
        ctyp = typ if self.mode == "scalar" else self.convert(typ,dl)
##        print("%s --> %s"%(typ,ctyp))
##        print("%s       "%orig_typ)
        nb_rand = str(dl['unit'].get("nb_rand","NT2_NB_RANDOM_TEST"))
        du =dl['unit']
        d = du["verif_test"]
        ##print("du[ranges] = %s"%du["ranges"])
        actual_ranges = du["ranges"].get(typ,du["ranges"].get("default",None))
        if actual_ranges is None :
            actual_ranges = du["ranges"].get(orig_typ,du["ranges"].get("default",None))
            self.__grouping_used = True
        ## print("ooooooo actual %s"%actual_ranges)
        if isinstance(d.get("property_value",[]), list) : return []
        if self.mode == "scalar" :
            durac = d.get("property_call",{})
            ##print("ooooooo durac %s"%durac)
            if durac is None : durac = {}
            if (len(durac.get(ctyp,durac.get("default",[])))== 0 and
                len(durac.get(orig_typ,durac.get("default",[])))== 0) : return []
        r = [
        "  // random verifications",
        "  static const nt2::uint32_t NR = %s;"%nb_rand,
        ]
##        print ("actual_ranges %s"%actual_ranges)
##        print ("typ %s"%typ)
        if isinstance(actual_ranges[0][0],str) : actual_ranges = [actual_ranges]
##        print("ooo actual_ranges = %s"%actual_ranges)
        for r1 in actual_ranges :
##            print("r1 %s" % r1)
##            print("ctyp %s"%ctyp)
            self.bg.orig_typ=orig_typ
            r +=self.bg.create_unit_txt_part( Random_verif_test_gen.Random_test_body[self.mode],self.__prepare,dl,ctyp,r1)
        return r

    def expand_to_list(self,typ) :
##        print("typ ->>> %s"%typ)
        return self.bg.Expansion_dict[self.platform].get(typ,typ)

    def loads(self, beg, df, arity) :
        s = []
        for i in xrange(0, arity) :
            t = self.__simd_get_typ(i,df)
            if t == 'iT' or ( t == 'ivT' and df.get("scalar_ints",False)) :
                s.append( beg+("iT a%s = tab_a%s[j];"%(str(i),str(i))))
            else :
                s.append( beg+("%s a%s = load<%s>(&tab_a%s[0],j);"%(t,str(i),t,str(i))))
        return s

    def buffers_creation(self, beg, df, arity, actual_range) :
        s = []
        tpdefs = df.get("type_defs",None)
        if tpdefs is not None :
            for l in tpdefs : s.append( beg+l)
        for i in xrange(0, arity) :
            j = min(i,len(actual_range)-1)
            rg0 =  actual_range[j][0]
            rg1 =  actual_range[j][1]
            t = self.__simd_get_typ(i,df)
            Mode = self.mode.upper() if t != 'iT' else "SCALAR"
            size = 'NR' if  t != 'iT' or Mode == 'SCALAR' else 'NR/cardinal_of<n_t>::value'
            s.append( beg+("NT2_CREATE_BUF(tab_a%d,"%(i))+ self.__get_typ(i,df)+(", %s, %s, %s);"%(size,rg0,rg1)) )
        s.append(beg+"double ulp0, ulpd ; ulpd=ulp0=0.0;")
        if self.mode == 'scalar' :
            ct = df["call_types"]
            lct = len(ct)
            if lct == 0 :
                typ = ['T']*arity
            elif lct == 1 :
                typ = ct[0]*arity
            else :
                typ = ct
            for i in range(arity) :
                c = "%s a%s;"%(typ[i],str(i))
                s.append(beg+c)
        return s

    def __prepare(self,s,typ,d,actual_range) :
#        print("s %s"%s)
        df = d.get("functor",self.Default_df)
        scalar_ints = df.get("scalar_ints",False)
        istpl = df.get("tpl","")
        arity = int(df.get("arity","1"))
        s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
        s=re.sub("\$plural\$", "s" if arity>1 else "",s)
        du = d["unit"]
        ret_arity = int(df.get("ret_arity","0"))
        dur= du["verif_test"]
        no_ulp =du["global_header"].get("no_ulp",False)
        no_ulp = False if no_ulp == 'False' else no_ulp
        nb_rand = str(dur.get("nb_rand","NT2_NB_RANDOM_TEST"))
        s=re.sub("\$nb_rand\$",nb_rand,s)
        m = re.match("( *)\$loads\$.*",s)
        if m : return self.loads(m.groups()[0],df,arity)
        m = re.match("( *)\$buffers_creation\$.*",s)
        if m : return self.buffers_creation(m.groups()[0],df,arity,actual_range)

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
        m = re.match("( *)\$max\$.*",s)
        if m :
            if no_ulp :
                s=re.sub("\$max\$","",s)
                return s
            else :
                s=re.sub("\$max\$",'std::cout << "max ulp found is: " << ulp0 << std::endl;',s)
                return s
        m = re.match("( *)\$calls\$.*",s)
        if m :
            call_param = ','.join([ "a%d" % i for i in xrange(0, arity) ])
            external = "" if self.bg.get_tb_style() == "sys" else self.bg.get_tb_name()+'::'
            std_call = "nt2::"+external+self.bg.get_fct_name()+istpl+'('+call_param+")"
            durac = dur.get("property_call",{"default" : [std_call]})
            if durac is None : durac = {"default" : [std_call]}
            durav = dur.get("property_value",{"default" : ["0"]})
##            print("oooooooo %s" %durav)
            durat = dur.get("ulp_thresh",{"default" : ["0"]})
            if type(durat) is str : durat = {"default" : ["0"]}
            beg = m.groups()[0]
            if self.mode == 'scalar' :
                if ret_arity >= 1:
                    r = [beg + 'r_t r = ' + std_call +";"]
                    tdef = beg+"typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,$i$>::type>::type r_t$i$;"
                    for i in xrange(0, ret_arity) : r.append(re.sub('\$i\$',str(i),tdef))
                    declare = beg+"r_t$i$ r$i$ = boost::fusion::get<$i$>(r);"
                    for i in xrange(0, ret_arity) :  r.append(re.sub('\$i\$',str(i),declare))
                    ##print("----------------no_ulp %s "%no_ulp)
                    if no_ulp :
                        tpl = "NT2_TEST_EQUAL( $property_call$,$property_value$);"
                        Call = beg+"NT2_TEST_EQUAL( r$i$, $property_value$);"
                    else :
                        tpl = "NT2_TEST_TUPLE_ULP_EQUAL( $property_call$,$property_value$,$ulp_thresh$);"
##                        Call = beg+"NT2_TEST_TUPLE_ULP_EQUAL( boost::fusion::get<$i$>(r), $property_value$, $ulp_thresh$);"
                        Call = beg+"NT2_TEST_TUPLE_ULP_EQUAL( r$i$, $property_value$, $ulp_thresh$);"
                    value = durav.get(typ,durav.get("default",None))
                    if value is None :
                        value =durav.get(self.bg.orig_typ,durav.get("default",None))
                        self.__grouping_used = True
                    if len(value) and isinstance(value[0],str) : value = [value]
                    for v in value :
                        for j in xrange(0,ret_arity) :
                            if (v[j] != 'no test available') :
                                thresh = durat.get(typ,durat.get("default",None))
##                                print("thresh %s"%thresh)
                                if thresh is None : thresh = durat.get(self.bg.orig_typ,durat.get("default",["0"]))
                                index = j if (len(thresh)>1) else 0
                                l = re.sub('\$ulp_thresh\$',thresh[index],Call)
                                l = re.sub("\$property_value\$" ,v[j],l)
                                l = re.sub("\$i\$" ,str(j),l)
                                r.append(l)
                                r.append(beg+"if (ulpd>ulp0) ulp0=ulpd;")
                    return r
                else :
                    r = []
                    dtmp = durac.get(typ,None)
                    if dtmp is None :
                        dtmp = durac.get(self.bg.orig_typ,durac.get("default",[]))
                        self.__grouping_used = True
                    spcall = dur.get('special_call',False)
                    if spcall :
                        r.extend(spcall)
                    else :
##                        print('here')
##                        print("oooooo durat %s"%durat)
##                        print("oooooo self.bg.orig_typ %s"%self.bg.orig_typ)
##                        print("oooooo durac %s"%durac)
                        length = len(dtmp)
##                        print("length %s"%length)
##                        print("dtmp   %s"%dtmp)
##                        print("durav  %s"%durav)
                        value = durav.get(typ,None)
                        if value is None or not len(value) :
                            value =durav.get(self.bg.orig_typ,durav.get("default",None))
##                        print("  self.bg.orig_typ %s"% self.bg.orig_typ)
##                        print("value   %s"%value)
                        for i in xrange(0, length) :
                            if no_ulp :
                                s = beg+"NT2_TEST_EQUAL( $property_call$,$property_value$);"
                            else :
                                s = beg+"NT2_TEST_ULP_EQUAL( $property_call$,$property_value$,$ulp_thresh$);"
                            thresh = durac.get(typ,None)
                            if thresh is None :
                                thresh = durat.get(self.bg.orig_typ,durat.get("default",["0"]))
                            j = i if len(thresh)>i else 0
                            s = re.sub('\$ulp_thresh\$',thresh[j],s)
                            #                    s=re.sub("\$fct_name\$",self.bg.get_fct_name(),s)
                            call = durac.get(typ,durac.get("default",None))
##                            print("ooooooo call %s"%call)
                            if call is None or not len(call) :
                                call = durac.get(self.bg.orig_typ,durac.get("default",None))
                                self.__grouping_used = True

##                            print("ooooooo call %s"%call)
                            s=re.sub("\$property_call\$" ,call[i],s)
                            s=re.sub("\$property_value\$" ,value[i],s)
                            r.append(s)
                    if not no_ulp : r.append(beg+"ulp0=nt2::max(ulpd,ulp0);")
                    return r
            else : ## simd
                print("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii")
                if ret_arity > 1 :
                    dtmp = durac.get(typ,None)
                    if dtmp is None :
                        dtmp = durac.get(self.bg.orig_typ,durac.get("default",[]))
                        self.__grouping_used = True
                    length = len(dtmp)
                    g = ','.join([ "a%d" % i for i in xrange(0, arity) ])
                    index = [ ('j' if self.__simd_get_typ(i,df) == 'iT' else 'k') for i in xrange(0, arity) ]
                    thresh = "0" if df.get("special",[""])[0] == "predicate" else durat.get("real","1.5")
                    if df.get("simd_ulp_thresh",False) : thresh = df.get("simd_ulp_thresh",False)
                    h = ','.join([ "tab_a%d[%s]" % (i,index[i]) for i in xrange(0, arity) ])
                    name = df.get("name",False)
                    if not name : name = self.bg.get_fct_name()

                    ULP = "" if no_ulp else "TUPLE_ULP_"
                    THR = "" if no_ulp else ", "+thresh
                    if not ( df.get("special",[""])[0] in ['swar']) :
                        r = [
                        "        r_t r = nt2::%s%s(%s);"%(name,istpl,g),
                        "        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)",
                        "        {",
                        "          nt2::uint32_t k = i+j*cardinal_of<n_t>::value;",
                        "          sr_t sr =  nt2::%s%s(%s);"%(name,istpl,h),
                        "          NT2_TEST_%sEQUAL( boost::fusion::get<0>(r)[i],"%(ULP),
                        "                                    boost::fusion::get<0>(sr)%s);"%(THR),
                        "          ulp0 = nt2::max(ulpd,ulp0);",
                        "          NT2_TEST_%sEQUAL( boost::fusion::get<1>(r)[i],"%(ULP),
                        "                                    boost::fusion::get<1>(sr)%s);"%(THR),
                        "          ulp0 = nt2::max(ulpd,ulp0);",
                        "        }",
                        ]
                    else :
                        r = ["        r_t v = %s%s(%s);"%(name,istpl,g)]
##                        print(dur)
                        r+= dur['scalar_simul'].get(typ,dur['scalar_simul']['default'])
                    return r
                else:
                    print("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj")
                    dtmp = durac.get(typ,None)
                    if dtmp is None :
                        dtmp = durac.get(self.bg.orig_typ,durac.get("default",[]))
                        self.__grouping_used = True
                    length = len(dtmp)
                    g = ','.join([ "a%d" % i for i in xrange(0, arity) ])
                    index = [ ('j' if self.__simd_get_typ(i,df,scalar_ints) == 'iT' else 'k') for i in xrange(0, arity) ]
                    thresh = "0" if df.get("special",[""])[0] == "predicate" else durat.get("real_","2.5")
                    if df.get("simd_ulp_thresh",False) : thresh = df.get("simd_ulp_thresh",False)
                    ##print('durat = %s'%durat)
                    ##print('thesh = %s'%thresh)
                    if isinstance(thresh,list) : thresh = thresh[0]
                    h = ','.join([ "tab_a%d[%s]" % (i,index[i]) for i in xrange(0, arity) ])
                    name = self.bg.get_fct_name()
                    pred_test = "!=0" if df.get("special",[""])[0] in ["predicate","fuzzy"] else ""
                    no_ulp = du["global_header"].get("no_ulp",False)
                    ULP = "" if no_ulp  else "ULP_"
                    THRESH = "" if no_ulp else (", "+thresh)
                    if df.get("special",[""])[0] in ['reduction','swar'] :
##                        print("kkkkkkkkkkkkkkkkk")
##                        print(durac)
##                        print("kkkkkkkkkkkkkkkkk")
                        alternate_call = durac.get('default',None)
                        if alternate_call is not None :
                            r = ["        r_t v = "+ durac.get('default',None)[0]+";"]
                        else :
                            r = ["        r_t v = %s%s(%s);"%(name,istpl,g)]
##                        print(dur)
                        r+= dur['scalar_simul'].get(typ,dur['scalar_simul']['default'])
                    else :
                        z = durac.get("simd_special",False)
                        if z :
                            call = "        r_t v = "+z+";"
                        else :
                            call = "        r_t v = %s%s(%s);"%(name,istpl,g)
                        r = [
                            call,
                            "        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)",
                            "        {",
                            "          nt2::uint32_t k = i+j*cardinal_of<n_t>::value;",
                            "          NT2_TEST_%sEQUAL( v[i]%s,ssr_t(nt2::%s%s (%s))%s);"%(ULP,pred_test,name,istpl,h,THRESH),
                            ]
                        if not no_ulp : r.append("          ulp0 = nt2::max(ulpd,ulp0);")
                        r.append("        }")
                    return r


        return s

    def __get_typ(self,i,d) :
        dd = d.get("call_types",None)
        if dd is None or  not len(dd) :
            return "T"
        elif type(dd) is str :
            return dd
        else :
            return dd[i]

    def __simd_get_typ(self,i,d, scalar_ints=False) :
        dd = d.get("call_types",None)
        if dd is None or not len(dd) :
            r = "vT"
        elif type(dd) is str :
            r = re.sub('T','vT',dd)
        else :
            r = re.sub('T','vT',dd[i])
        if self.bg.get_fct_name()[-1]=='i' or scalar_ints :
            r = re.sub('ivT','iT',r)
        return r

    def convert(self,types,d) :
        d1 = d.get("unit",None)
        if d1 is None : return types
        d1 =  d1.get("verif_test",None)
        if d1 is None : return types
        d1 =  d1.get("simd",None)
        if d1 is None : return types
        tt = d1.get(types,None)
        if not (tt is None) :
            return tt
        return types



if __name__ == "__main__" :
    from pprint        import PrettyPrinter
    from unit_base_gen import Base_gen
    from unit_type_header_gen import Type_header_test_gen
    from unit_tuple_random_gen import Random_tuple_test_gen
    from unit_specific_values_gen import Specific_values_test_gen
    print __doc__
    bg = Base_gen("exponential",'pipo','scalar')
    dl = bg.get_fct_dict_list()
    r = []
    for d in dl :
        types = bg.recover("types",d["functor"],[])
        d_unit = d["unit"]
        for typ in types :
            thg = Type_header_test_gen(bg,d,typ,0)
            r+=thg.get_gen_beg()
##            if d_unit.get("specific_values",None) :
##                svt = Specific_values_test_gen(bg,d,typ)
##                r += svt.get_gen_result()
            if d_unit.get("random_tuple_test",None) :
                rtg = Random_tuple_test_gen(bg,d,typ)
                r += rtg. get_gen_result()
            if d_unit.get("verif_test",None) :
                vtg = Random_verif_test_gen(bg,d,typ)
                r += vtg. get_gen_result()
            r+=thg.get_gen_end()
    PrettyPrinter().pprint(r)
