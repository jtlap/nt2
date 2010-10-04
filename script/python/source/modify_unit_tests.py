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

import os
import sys
import re
from archi      import Sse, Vmx
from nt2_base   import Nt2
from fctor      import Functor
from file_utils import read, write, exist, mkdir
from mylogging  import Mylogging
from list_utils import show
from re_list    import sub_list

class ModifyUnitTests(Nt2) :
    """ Add/remove lines in unit test"""
    Datas = {'scalar' : {'length' : 41},
             "simd"   : {'length' : 41}
             }
    Replacemnt = {
##        ' - unit' : ' - #fct_name',
        ' :iceil' : "#fctname",
        'iceil'   : "#fctname"
        }
    Strait_Insertions = {
#        '#include <nt2/sdk/functor/meta/call.hpp>' : 10,
#        '#include <nt2/toolbox/#tb_name/include/#fct_name.hpp>' :10,
#        '#include <boost/type_traits/is_same.hpp>':10,
        }
    Final_Insertions = [
        """NT2_TEST_CASE_TPL ( :#fct_name,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                          (bool)
                  )
{
  using nt2::#fct_name;
  using nt2::functors::#fct_name_;

  //NT2_TEST( (boost::is_same < typename nt2::meta::call<#fct_name_(T)>::type
  //            , bool
  //            >::value)
  //         );
  //NT2_TEST_EQUAL(  #fct_name( T(42) ), T(42) );
  //NT2_TEST_EQUAL(  #fct_name( T(-42) ), -T(-42) );
  //NT2_TEST(  #fct_name(T(1337))  );
  //NT2_TEST( !#fct_name(T(0))     );
}
          """ 
        ]
    def __init__(self, tb_list = None, scalar_or_simd=None, datas = None) :
        Nt2.__init__(self)
        self.__tb_list = self.get_all_toolboxes() if tb_list is None else tb_list
        self.__sc_si   = "scalar" if scalar_or_simd is None else scalar_or_simd
        self.__datas   = ModifyUnitTests.Datas if datas is None else datas 

    def get_all_toolboxes(self) :
        p = self.absolute_path_to_mode()
        return [ f for f in os.listdir(p) if exist(os.path.join(p,f+'.hpp'))]

    def get_unit_dir(self,tb_name) :
        p = self.absolute_path_to_mode()
        p1 = os.path.join(p,tb_name,'unit',self.__sc_si)
        return p1
    
    def get_unit_test_list(self, tb_name) :
        return [ f[:-4] for f in os.listdir(self.get_unit_dir(tb_name)) if f[-4:] == '.cpp']

    def get_cpp_to_modify(self, tb_name) :
        cpp_list = self.get_unit_test_list(tb_name)
        unit_dir = self.get_unit_dir(tb_name)
        l = []
        for cpp in cpp_list :
            p = os.path.join(unit_dir,cpp+'.cpp')
            s = read(p)
            print len(s)
            if len(s) == self.__datas[self.__sc_si]['length'] :
                l.append(cpp)
        return l

    def modify_cpp(self,tb_name,cpps) :
        unit_dir = self.get_unit_dir(tb_name)
        d = {}
        if type(cpps) is str :
            d["#fct_name"]= cpps
            d["#tb_name"] = tb_name
            repls = self.update_replacmnt(d)
##            sinserts = self.update_strait_insertions(d)
##            finserts = self.update_final_insertions(d)
            p = os.path.join(unit_dir,cpps+'.cpp')
            s = read(p)
            s,doner = self.mk_replace(s,repls)
##            s,dones = self.mk_inserts(s,sinserts)
##            s,donef = self.mk_insertf(s,finserts)
            if True or doner :#or dones or donef:
                print "%s was modified" % cpps
                #show(s)
                self.update(s,d)
                #                show(s)
                write(p,s,False)

        else :
            for cpp in cpps :
                self.modify_cpp(tb_name,cpp)

    def update_replacmnt(self,d) :
        repls = ModifyUnitTests.Replacemnt.copy();
        for k in d.keys() :
            for k1 in repls.keys() :
                repls[k1]=re.sub(k,d[k],repls[k1])
        return repls
    
    def update(self,s,d) :
        for k in d.keys() :
            for i,ls in enumerate(s) :
                s[i]=re.sub(k,d[k],ls)
        return s
    
    def update_strait_insertions(self,d) :
        repls = ModifyUnitTests.Strait_Insertions.copy();
        for k in d.keys() :
#            print "k %s d[k] %s"% (k,d[k])
            for k1 in repls.keys() :
#                print "k1 %s d[k] %s"% (k1,repls[k1])
                k1=re.sub(k,d[k],k1)
        return repls

    def update_final_insertions(self,d) :
        repls = ModifyUnitTests.Final_Insertions;
        for k in d.keys() :
#            print "k %s d[k] %s"% (k,d[k])
             for i,k1 in enumerate(repls) :
#                print "k1 %s d[k] %s"% (k1,repls[k1])
                repls[i]=re.sub(k,d[k],k1)
        return repls

    def mk_replace(self,s,repls) :
        wr = False
        for target in repls.keys() :
            st ='\n'.join(s)
            if re.search(target,st) :
                s=sub_list(target, repls[target],s)
                wr=True
        return (s, wr)

    def mk_inserts(self,s,inserts) :
        wr = False
        for target in inserts.keys() :
            st ='\n'.join(s)
            if not re.search(target,st) :
                if type(inserts[target]) is int :
                    s.insert(inserts[target],target)
                wr=True
        return (s, wr)
      
    def mk_insertf(self,s,insertf) :
        wr = False
        for target in insertf :
            st ='\n'.join(s)
            if not re.search(target,st) :
                s.append(target)
                wr=True
        return (s, wr)
      
if __name__ == "__main__":
    Mylogging.set_level('CRITICAL')
    f = ModifyUnitTests(tb_list = ["arithmetic"],
                        scalar_or_simd = "scalar")

      
   
##    pair=f.get_unit_test_list("arithmetic")
##    print pair[0]
##    show(pair[1])
    cpps = f.get_cpp_to_modify("arithmetic")
    f.modify_cpp("arithmetic", cpps)
