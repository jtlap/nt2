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

class Insert(Functor) :
    """ insert files where needed"""
    Insertions = {
##        "Minf<.*>"    : "#include <nt2/sdk/constant/infinites.hpp>", 
##        "Inf<.*>"     : "#include <nt2/sdk/constant/infinites.hpp>", 
##        "Nan<.*>"     : "#include <nt2/sdk/constant/real.hpp>",
##        "Half<.*>"    : "#include <nt2/sdk/constant/real.hpp>",
##        "Mhalf<.*>"   : "#include <nt2/sdk/constant/real.hpp>",
##        "Mzero<.*>"   : "#include <nt2/sdk/constant/real.hpp>",
##        "Half<.*>"    : "#include <nt2/sdk/constant/real.hpp>",
##        "Third<.*>"   : "#include <nt2/sdk/constant/real.hpp>",
##        "Quarter<.*>" : "#include <nt2/sdk/constant/real.hpp>",
##        "Pi<.*>" : "#include <nt2/sdk/constant/real.hpp>",
##        "Eps<.*>" : "#include <nt2/sdk/constant/eps_related.hpp>",
##        "Ldexpmask<.*>" : "#include <nt2/sdk/constant/real.hpp>",
##        "Mten<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mnine<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Meight<.*>"  : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mseven<.*>"  : "#include <nt2/sdk/constant/digits.hpp>",
##        "Msix<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mfive<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mfour<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mthree<.*>"  : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mtwo<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Mone<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Zero<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "One<.*>"     : "#include <nt2/sdk/constant/digits.hpp>",
##        "Two<.*>"     : "#include <nt2/sdk/constant/digits.hpp>",
##        "Three<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Four<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Five<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Six<.*>"     : "#include <nt2/sdk/constant/digits.hpp>",
##        "Seven<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Eight<.*>"   : "#include <nt2/sdk/constant/digits.hpp>",
##        "Nine<.*>"    : "#include <nt2/sdk/constant/digits.hpp>",
##        "Ten<.*>"     : "#include <nt2/sdk/constant/digits.hpp>",
##        "True<.*>"    : "#include <nt2/sdk/constant/boolean.hpp>",
##        "False<.*>"   : "#include <nt2/sdk/constant/boolean.hpp>",
##        "boost::fusion" : "#include <boost/fusion/tuple.hpp>",
##        "boost::mpl::vector" : "#include <boost/mpl/vector.hpp>",
##        "boost::math"        : "#include <boost/math/special_functions.hpp>",
##        "int32_t_"           : "#include <nt2/sdk/meta/templatize.hpp>",
##        "Valmax<.*>"            :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Valmin<.*>"            :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Smallestposval<.*>"    :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Signmask<.*>"          :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Maxleftshift<.*>"      :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Mindenormal<.*>"       :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Nbmantissabits<.*>"    :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Nbexponentbits<.*>"    :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Maxexponent<.*>"       :   "#include <nt2/sdk/constant/properties.hpp>",
##        "Minexponent<.*>"       :   "#include <nt2/sdk/constant/properties.hpp>",
##        "is_floating_point<.*>" : "#include <nt2/sdk/meta/adapted_traits.hpp>",
##        "as_integer<.*>"        : "#include <nt2/sdk/meta/as_integer.hpp>",
##        "as_bits<.*>"           : "#include <nt2/sdk/meta/as_bits.hpp>",
##        "as_signed<.*>"           : "#include <nt2/sdk/meta/as_signed.hpp>",
##        "ignore_unused"         : "#include <nt2/sdk/details/ignore_unused.hpp>",
##        "is_real_convertible<.*>":"#include <nt2/sdk/simd/meta/is_real_convertible.hpp>"
##        "int64_t_"               : "#include <nt2/sdk/meta/templatize.hpp>",
##        "integral_constant<.*>"  : "#include <nt2/sdk/constant/digits.hpp>",
##        "Splitfactor<.*>"        : "#include <nt2/sdk/constant/real.hpp>",
##        "has_larger_or_equal_size": "#include <nt2/sdk/meta/size.hpp>",
##        "downgrade" : "#include <nt2/sdk/meta/downgrade.hpp>",
##        "float_"               : "#include <nt2/sdk/meta/templatize.hpp>",
##        "upgrade" : "#include <nt2/sdk/meta/upgrade.hpp>",
##        "has_same_size" : "#include <nt2/sdk/meta/size.hpp>",
##        "as_real<.*>"        : "#include <nt2/sdk/meta/as_real.hpp>",
##        "from_bits"         : "#include <nt2/sdk/meta/from_bits.hpp>",
##        "Nbdigits<.*>" : "#include <nt2/sdk/constant/properties.hpp>",
        }
    Replacement = {
##        "simd::sse_" :"tag::sse_",
##        "is_floating_point_convertible" :  "is_real_convertible",
##        "Const *<" : "integral_constant<",
##        "{ typedef A0 type; };" : ": meta::strip<A0>{};//",
##        "integral_downgrade" : "downgrade",
##        "integral_upgrade"   : "upgrade",
##        "Category"           : "Extension",
##        "simd::map" : "map",
##        ", typename nt2::meta::scalar_of<A0>::type" : ", A0",
##        "#include <nt2/include/functions/splat.hpp>" :"",
##        "#include <nt2/include/functions/bitwise_and.hpp>":"",
##        "#include <nt2/include/functions/bitwise_or.hpp>":"",
##        "#include <nt2/include/functions/bitwise_xor.hpp>":"",
##        "typename nt2::meta::scalar_of<A1>::type" : "A1",      
##        "#include <nt2/include/nt2/toolbox/" : "#include <nt2/toolbox/",
##        ",not_simd_type" : ",tag::not_simd_type",
##        ", *simd_type": ", tag::simd_type",
##        "#include <nt2/toolbox/trigonometric/function/simd/impl/" :" #include <nt2/toolbox/trigonometric/function/simd/common/impl/",      
        "nt2/include/functions/details/simd/common/": "nt2/include/functions/",
    }
    def __init__(self, tb_name, style='sys') :
        Functor.__init__(self,tb_name,'modify','sys')
        p = os.path.join(self.get_path_to_nt2(),'nt2/toolbox',tb_name)
        self.__mk_list_dirs()
        self.__mk_list_hpps()

    def __mk_list_dirs(self) :
        p = os.path.join(self.get_path_to_nt2(),'nt2/toolbox',
                         self.get_tb_name())
        self.__list_dirs = []
        for d in Functor.Tb_tree[12:] :
            self.__list_dirs.append(os.path.join(p,d))
        del self.__list_dirs[1]
        
    def __mk_list_hpps(self) :
        p = self.__list_dirs[0]
        self.__list_hpps = [ f for f in os.listdir(p) if f[-4:]=='.hpp']

    def get_list_dirs(self) : return self.__list_dirs
    def get_list_hpps(self) : return self.__list_hpps
    
    def get_matches(self,target) :
        for d in self.get_list_dirs() :
            for h in self.get_list_hpps() :
                f = os.path.join(d,h)
                if exist(f) :
                    s = read(f)
                    st ='\n'.join(s)
                    if re.search(target,st) :
                       rep = Insert.Insertions[target]
                       if not re.search(rep,st) :
                           s.insert(10,rep)
                           write(f,s,False)
                           print "%s -> %s"%(target,h)
        
    def get_replacmt(self,target) :
        for d in self.get_list_dirs() :
            for h in self.get_list_hpps() :
                f = os.path.join(d,h)
                if exist(f) :
                    s = read(f)
                    st ='\n'.join(s)
                    if re.search(target,st) :
                       s=sub_list(target, Insert.Replacement[target],s)
                       write(f,s,False)
                       print "%s -> %s"%(target,Insert.Replacement[target])
        

if __name__ == "__main__":
    Mylogging.set_level('CRITICAL')
    for tb in Recover.Toolbox_List :
        i = Insert(tb) #"arithmetic")
        for target in Insert.Insertions.keys() :
            i.get_matches(target)
        for target in Insert.Replacement.keys() :
            i.get_replacmt(target)

sys.path.pop(0)
