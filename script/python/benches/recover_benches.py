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
           recover_benches.py <tb_name>

   
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

class Recover_benches :
    Scal_types = ['float','double','int64_t','int32_t','int16_t','int8_t','uint64_t','uint32_t','uint16_t','uint8_t']
    Simd_types = ['vfloat','vdouble','vint64_t','vint32_t','vint16_t','vint8_t','vuint64_t','vuint32_t','vuint16_t','vuint8_t']
    Scal_base  = [
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
        "",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Scalar Runtime benchmark for functor<$name$_> from $tb_name$",
        "//////////////////////////////////////////////////////////////////////////////",
        "using nt2::functors::$name$_;",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// range macro",
        "//////////////////////////////////////////////////////////////////////////////",
        "#define RS(T,V1,V2) (T, T(V1) , T(V2))",
        "",
        "",
        "#undef RS"
        ]
    Simd_base  = [
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
        "#include <nt2/sdk/simd/native.hpp>",
        "#include <cmath>",
        "",
        "typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// Simd Runtime benchmark for functor<$name$_> from $tb_name$",
        "//////////////////////////////////////////////////////////////////////////////",
        "using nt2::functors::$name$_;",
        "",
        "//////////////////////////////////////////////////////////////////////////////",
        "// range macro",
        "//////////////////////////////////////////////////////////////////////////////",
        "#define RS(T,V1,V2) (T, V1 , V2)",
        "",
        "",
        "#undef RS"
        ]
    
    def __init__(self, tb_name='trigonometric',
                 mode = 'modify',
                 style='usr') :
        self.__tb_name    = tb_name
        self.__old_bench_path   = '/home/jt/DevC++/dev_lasmea/docnt4/nt2-cleanup/test/test_sse_g++-4.3/'
        self.__new_bench_path   = os.path.join('/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox',tb_name,'bench')
        self.__new_scal_path  = os.path.join(self.__new_bench_path,'scalar')
        self.__new_simd_path  = os.path.join(self.__new_bench_path,'simd')

    def get_tb_name(self)   : return self.__tb_name
    def get_old_bench_path(self)  : return self.__old_bench_path
    def get_new_bench_path(self)  : return self.__new_bench_path
    def get_new_scal_path(self) : return self.__new_scal_path
    def get_new_simd_path(self) : return self.__new_simd_path
    def get_new_path(self,mode) : return self.__new_scal_path if mode[:4] == 'scal' else self.__new_simd_path
    def get_functor_list(self) :
        l = []
        print self.get_new_bench_path()
        for name in os.listdir(self.get_new_scal_path()) :
            if name[-4:]=='.cpp' :
                h = name[:-4]
                if exist(os.path.join(self.get_old_bench_path(),'time_'+name)) :
                    l.append(h)
        return l
    
    def get_old_bench_text(self,name) :
        return read(os.path.join(self.get_old_bench_path(),'time_'+name+'.cpp'))
                    
    def get_type_list(self,mode) :
        if mode[:4] == 'scal' :
            return Recover_benches.Scal_types
        else :
            return Recover_benches.Simd_types

    def get_base(self,mode) :
        if mode[:4] == 'scal' :
            return Recover_benches.Scal_base
        else :
            return Recover_benches.Simd_base
        
    def get_benched_types(self,old_bench_text,mode) :
        type_list = self.get_type_list(mode)
        s = ' '.join(old_bench_text)
        return [ t for t in type_list if s.find('('+t)>=0]
        #        show(  benched_types)             

    def get_range(self,name,old_bench_text,typ) :
        for l in old_bench_text :
            m = re.search(' *(NT2_TIMING\( *nt2::functors::'+name+'_ *, *\(RS\('+typ+'.*\))$',l) 
            if m : return m.groups()[0]
        return ""
    def define_types(self,old_bench_text,mode):
        if mode[:4] == 'scal' :
            return []
        else :
           return [
               'typedef nt2::simd::native<'+typ[1:]+',ext_t> '+typ+';'
               for typ in self.get_benched_types(old_bench_text,mode) 
               ]
               
    
    def get_range_list(self,name,old_bench_text,mode) :
        return [ self.get_range(name,old_bench_text,typ) for typ in self.get_benched_types(old_bench_text,mode)]

    def make_new_bench_file(self,name,mode) :
        oldb = self.get_old_bench_text(name)
        newb = self.get_base(mode)
        newb = sub_list('\$name\$',name,newb)
        newb = sub_list('\$tb_name\$',self.get_tb_name(),newb)
        newb = newb[:14]+self.define_types(oldb,mode)+newb[14:]
        newb = newb[:-2]+sub_list(' ','',self.get_range_list(name,oldb,mode))+newb[-2:]
        #        show(newb)
        write(os.path.join(self.get_new_path(mode),name+'.cpp'),newb,False)
        
    def make_new_benches(self,mode) :
        fctrs = self.get_functor_list()
        for name in fctrs :
            print "making %s bench file for %s" %(mode,name)
            self.make_new_bench_file(name,mode)


if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    length = len(sys.argv)
    if length == 2 :
##        old = Recover_benches(sys.argv[1])
##        old.make_new_benches('scalar')
##        old.make_new_benches('simd')
    else :
        print __doc__

sys.path.pop(0)
           
       

