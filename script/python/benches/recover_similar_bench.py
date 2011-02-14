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


"""User utility to recover benches spec from old Nt2
   usage:
           recover_similar_benchs.py <for_tb_name>

   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
import re
from fctor      import Functor
from file_utils import read, write,exist
from mylogging  import Mylogging
#from scalar_extract import get_validate, get_call
from list_utils import show
from re_list    import sub_list
from toolbox_list import Toolboxes

class Recover_similar_benchs :
    Default_bench = [
        "//////////////////////////////////////////////////////////////////////////////",
        "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
        "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
        "///",
        "///          Distributed under the Boost Software License, Version 1.0",
        "///                 See accompanying file LICENSE.txt or copy at",
        "///                     http://www.boost.org/LICENSE_1_0.txt",
        "//////////////////////////////////////////////////////////////////////////////",
        "#include <nt2/toolbox/$tb_name$/include/$name$.hpp>",
        "#include <nt2/sdk/unit/benchmark.hpp>",
        "#include <cmath>",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Scalar Runtime benchmark for functor<$name$_> from $tb_name$",
        "//////////////////////////////////////////////////////////////////////////////",
        "using nt2::$tb_name$::$name$_;",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// range macro",
        "//////////////////////////////////////////////////////////////////////////////",
        "#define RS(T,V1,V2) (T, T(V1) , T(V2))",
        "",
        "// TO DO Check ranges",
        "NT2_TIMING(nt2::$tb_name$::$name$_,$typ_float$)",
        "NT2_TIMING(nt2::$tb_name$::$name$_,$typ_double$)",
        "NT2_TIMING(nt2::$tb_name$::$name$_,$typ_int32_t$)",
        "",
        "#undef RS",
        ]
    
    def __init__(self, for_tb_name) :
        self.__tb_list    = Toolboxes().get_sys_tb_list()
        self.__tb_name    = for_tb_name
        self.__tbs_path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox')

    def get_tb_name(self)   : return self.__tb_name
    def get_tb_list(self)   : return self.__tb_list
    def get_tbs_path(self)  : return self.__tbs_path
    def get_tb_path(self,tb_name) : return  os.path.join(self.get_tbs_path(),tb_name)
    def get_functor_list(self,tb_name,style) :
        l = []
        for name in os.listdir(os.path.join(self.get_tb_path(tb_name),'bench',style)) :
            if name[-4:]=='.cpp' :
                h = name[:-4]
                l.append(h)
        return l
             
    def find_similar_fctor(self, name,style) :
        for tb_name in self.get_tb_list() :
            l = self.get_functor_list(tb_name,style)
            if name in l : return tb_name
            if name[:-3] in l :
                if name[-3:] in ['_rn','_ru','_rz','_rd'] :
                    return tb_name
        return None

    def replace_bench(self,name,style) :
        tb_name = r.find_similar_fctor(name,style)
        if tb_name is not None :
#            print "avant"
            s = self.read_similar(tb_name,name,style)
#            show(s)
            s = self.adapt_similar(s,name,tb_name)
            print "tb %s contains %s"% (tb_name,name)
        else :
            print "icitte"
            s = self.default(name,self.get_arity(name))
            #        show(s)
        return s

    def get_arity(self,name) :
        p = os.path.join(self.get_tb_path(self.get_tb_name()),'function',name+'.hpp')
        s = read(p)
        for l in s :
            m = re.search('  NT2_FUNCTION_IMPLEMENTATION',l)
            if m :
                #            print "l = %s " % l
                m = re.search('([0-9]+)\)',l)
                if m :
                    #                print " arity %s "% m.groups()[0]
                    return int(m.groups()[0])
            else :
                m = re.search('  NT2_CRLIBM_FUNCTION_IMPLEMENTATION_TPL',l)
                if m :
                    #            print "l = %s " % l
                    m = re.search('([0-9]+)\)',l)
                    if m :
                        #                print " arity %s "% m.groups()[0]
                        return int(m.groups()[0])
                    
        return ""
         
    def replace_benchs(self,style) :
        fctrs = self.get_functor_list(self.get_tb_name(),style)
        for name in fctrs :
            s = self.replace_bench(name,style)
##            print "----------------------------"
##            show(s)
##            print "============================"
            self.write_bench(name,style,s)
        
    def write_bench(self,name,style,s):
        p = os.path.join(self.get_tb_path(self.get_tb_name()),'bench',style,name+'.cpp')
        print name
#        print "apr-Aès"-b
#        show(s)
        write(p,s,False)

    def read_similar(self,tb_name,name,style) :
         p = os.path.join(self.get_tb_path(tb_name),'bench',style,self.strip(name)+'.cpp')
         return read(p)

    def strip(self,name) :
        if name[-3:] in ['_rn','_ru','_rz','_rd'] :
            return name[:-3]
        else :
            return name
        
    def decorate(self,name) :
        if name[-3:] in ['_rn','_ru','_rz','_rd'] :
            return name
        else :
            return name+'<rn>'

    def adapt_similar(self,s,name,old_tb_name) :
        new_tb_name = self.get_tb_name()
        old_name = self.strip(name)
        new_name = self.decorate(name)
        print "old %s -> new %s"% (old_name,new_name)
        if old_name == name : # template case
            s = sub_list(' '+old_name+'\(',' '+new_name+'(',s)
            s = sub_list(old_tb_name,new_tb_name,s)
            s = sub_list("nt2::functors::"+old_name,"nt2::"+new_tb_name+"::"+old_name,s)
            s = sub_list(old_name+'<rn>_',old_name+'_<rn>',s)
            s = sub_list("<rn>","<nt2::rn>",s)
            s = sub_list("NT2_TIMING\(nt2::crlibm::"+old_name+"_","NT2_TIMING(nt2::crlibm::"+old_name+"_<nt2::rn>",s)
        else :
            s = sub_list("nt2::functors::","nt2::"+new_tb_name+"::",s)
            s = sub_list(old_tb_name,new_tb_name,s)
            s = sub_list(old_name,new_name,s)
        return s

    
    def default(self,name,arity) :
        s =  Recover_similar_benchs.Default_bench
        new_tb_name = self.get_tb_name()
        s = sub_list("\$tb_name\$",new_tb_name,s)
        s = sub_list("\$name\$",name,s)
        s = sub_list("\$typ_"+"float"+"\$", "(RS(float,-1.0f,1.0f))"*arity,s)
        s = sub_list("\$typ_"+"double"+"\$", "(RS(double,-1.0f,1.0f))"*arity,s)
        s = sub_list("\$typ_"+"int32_t"+"\$", "(RS(int32_t,-1,1))"*arity,s)
        return s
    
if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
##        r = Recover_similar_benchs(sys.argv[1])
##        r.replace_benchs('scalar')
##        r.replace_benchs('simd')
    else :
        print __doc__

sys.path.pop(0)
           
       

