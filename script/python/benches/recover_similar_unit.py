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
           recover_similar_units.py <for_tb_name>

   
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

class Recover_similar_units :
    Default_unit = [
        "//////////////////////////////////////////////////////////////////////////////",
        "///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand",
        "///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI",
        "///",
        "///          Distributed under the Boost Software License, Version 1.0",
        "///                 See accompanying file LICENSE.txt or copy at",
        "///                     http://www.boost.org/LICENSE_1_0.txt",
        "//////////////////////////////////////////////////////////////////////////////",
        '#define NT2_UNIT_MODULE "nt2 $tb_name$ toolbox - $name$ - unit/scalar Mode"',
        "#include <nt2/include/functions/acos.hpp> ",
        "#include <nt2/toolbox/$tb_name$/include/$name$.hpp>",
        "#include <nt2/sdk/unit/tests.hpp>",
        "#include <nt2/sdk/unit/module.hpp>",
        "#include <nt2/sdk/functor/meta/call.hpp>",
        "#include <boost/type_traits/is_same.hpp>",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "//Test behavior of $tb_name$ component $name$ using NT2_TEST_CASE",
        "//////////////////////////////////////////////////////////////////////////////",
        "NT2_TEST_CASE_TPL ( $name$,  (double)(float) )",
        "{",
        "  using nt2::$tb_name$::$name$;",
        "  using nt2::$tb_name$::$name$_;",
        "",
        "  NT2_TEST( (boost::is_same<typename nt2::meta::call<nt2::$tb_name$::$name$_($list$)>::type,",
        "                           T",
        "                           >::value)",
        "          );",
        "}"
        ]
    
    def __init__(self, for_tb_name,
                 mode = 'modify',
                 style='usr') :
        self.__tb_list    = Toolboxes().get_sys_tb_list()
        self.__tb_name    = for_tb_name
        self.__tbs_path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox')

    def get_tb_name(self)   : return self.__tb_name
    def get_tb_list(self)   : return self.__tb_list
    def get_tbs_path(self)  : return self.__tbs_path
    def get_tb_path(self,tb_name) : return  os.path.join(self.get_tbs_path(),tb_name)
    def get_functor_list(self,tb_name) :
        l = []
        for name in os.listdir(os.path.join(self.get_tb_path(tb_name),'unit/scalar')) :
            if name[-4:]=='.cpp' :
                h = name[:-4]
                l.append(h)
        return l
             
    def find_similar_fctor(self, name) :
        for tb_name in self.get_tb_list() :
            l = self.get_functor_list(tb_name)
            if name in l : return tb_name
            if name[:-3] in l :
                if name[-3:] in ['_rn','_ru','_rz','_rd'] :
                    return tb_name
        return None

    def replace_scalar_unit(self,name) :
        tb_name = r.find_similar_fctor(name)
        if tb_name is not None :
            s = self.read_similar(tb_name,name)
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
         
    def replace_scalar_units(self) :
        fctrs = self.get_functor_list(self.get_tb_name())
        for name in fctrs :
            s = self.replace_scalar_unit(name)
##            print "----------------------------"
            show(s)
##            print "============================"
            p = os.path.join(self.get_tb_path(self.get_tb_name()),'unit/scalar',name+'.cpp')
            print p
            write(p,s,False)
            
    def strip(self,name) :
        if name[-3:] in ['_rn','_ru','_rz','_rd'] :
            return name[:-3]
        else :
            return name
        
    def decorate(self,name) :
        if (self.get_tb_name() != "crlibm") or (name[-3:] in ['_rn','_ru','_rz','_rd']) :
            return name
        else :
            return name+'<rn>'
 
    def read_similar(self,tb_name,name) :
        name = self.strip(name)
        p = os.path.join(self.get_tb_path(tb_name),'unit/scalar',name+'.cpp')
        return read(p)

    def adapt_similar(self,s,name,old_tb_name) :
        new_tb_name = self.get_tb_name()
        old_name = self.strip(name)
        new_name = self.decorate(name)
        print "old %s, new %s"% (old_name,new_name)
        if old_name == name and new_tb_name =="crlibm" : # template case
            s = sub_list(' '+old_name+'\(',' '+new_name+'(',s)
            s = sub_list(old_tb_name,new_tb_name,s)
            s = sub_list("using nt2::"+old_name,"using nt2::"+new_tb_name+"::"+old_name,s)
            s = sub_list("using nt2::functors::"+old_name,"using nt2::"+new_tb_name+"::"+old_name,s)
            s = sub_list("nt2::"+old_name,"nt2::"+new_tb_name+"::"+new_name,s)
            s = sub_list(old_name+'_\(',new_name+'_(',s)
            s = sub_list(old_name+'<rn>_',old_name+'_<rn>',s)
            s = sub_list("<rn>","<nt2::rn>",s)
        else :
            s = sub_list(old_tb_name,new_tb_name,s)
            s = sub_list(' '+old_name+'\(',' '+new_name+'(',s)
            s = sub_list(old_name+'\.hpp',new_name+'.hpp',s)
            s = sub_list(' '+old_name+',',' '+new_name+',',s)
            s = sub_list("using nt2::"+old_name,"using nt2::"+new_tb_name+"::"+new_name,s)
            s = sub_list("using nt2::functors::"+old_name,"using nt2::"+new_tb_name+"::"+new_name,s)
            s = sub_list("nt2::"+old_name,"nt2::"+new_tb_name+"::"+new_name,s)
            s = sub_list(old_name+'_\(',new_name+'_(',s)
        return s
    
    def default(self,name,arity) :
        s =  Recover_similar_units.Default_unit
        new_tb_name = self.get_tb_name()
        s = sub_list("\$tb_name\$",new_tb_name,s)
        s = sub_list("\$name\$",name,s)
        def strlist(tpl,n=1,sep = ", ") :
            s = tpl % (n*(0,))
            tpl =sep+tpl
            for i in range(1,arity) :
                s += tpl % (n*(i,))
            return s
        s = sub_list("\$list\$",strlist("T",0),s)
        return s
    
if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
##        r = Recover_similar_units(sys.argv[1])
##        r.replace_scalar_units()
    else :
        print __doc__

sys.path.pop(0)
           
       

