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


"""bench test generation for a functor
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
import re
import shutil
from pprint                          import PrettyPrinter

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from display_utils                   import show
from files_utils                     import write, exist
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_modules                     import Nt2_modules
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from unit_base_gen                   import Base_gen
sys.path.pop(0)

from bench_gen                       import Bench_gen



def create_one_bench(tb_name,
                     fct_name,
                     mode,
                     simd_type) :
    print("tb %s -> fct -> %s with %s mode -> simd_type %s"%(tb_name,fct_name,mode,simd_type))
    bg = Base_gen(tb_name,fct_name,mode)
##    print(bg.get_module_style(tb_name))
    bbg =  Bench_gen(bg,simd_type)
    return bbg.get_gen_result()

def write_bench(tb_name,fct_name,mode,s,check=False,backup=True) :
    nfp = Nt2_fct_props(tb_name,fct_name,mode)
    print("mode %s"%mode)
    p = nfp.get_fct_bench_path(mode)
##    print ('p = %s'%p)
    if backup and exist(p) :
##        print("p=%s" %p)
        i = 1;
        while True :
            pi = p+'.'+str(i)+'.bak'
            if not(exist(pi)) : break
            i += 1
        print("backing to %s"% pi)
        shutil.copy(p,pi)
    print "writing to %s"%p
    write(p,s,check)

def create_bench(tb_name, fct_list=None,
                modes=('scalar','simd'),
                show=True,
                write_files=False,
                check_on_write=True,
                backup_on_write=True,
                simd_type='sse') :
    bg = Nt2_modules()
##    print(bg.get_module_style(tb_name))
    if bg.get_module_style(tb_name) == 'usr' : modes = ['scalar']
    if fct_list is None :
        fcts = Nt2_tb_props(tb_name).get_fcts_list()
    elif isinstance(fct_list,str ) :
        fcts = [fct_list]
    else :
        fcts = fct_list
    if  isinstance(modes,str ) : modes = [modes]
    for fct in fcts :
        for mode in modes :
##            print("fct=%s,mode=%s"%(fct,mode))
            r= create_one_bench(tb_name,fct,mode,simd_type)
            if r is None :
                print('error for %s' % fct)
            elif len(r)==0 :
                print('no regeneration possible for %s %s-tests, please do it manually' % (fct,mode))
            else :
                just = "just" if show and not write_files else ""
                if show :
                    print("%s showing text of %s.cpp for %s-test"% (just,fct,mode))
                    print("<"+"="*40)
                    PrettyPrinter().pprint(r)
                    print("="*40+">")
                if write_files :
                    print("writing text of %s.cpp for %s-test"% (fct,mode))
                    write_bench(tb_name,fct,mode,r,
                               check=check_on_write,
                               backup=backup_on_write)


if __name__ == "__main__" :
    tb_name = "bitwise"
    fcts = Nt2_tb_props(tb_name).get_fcts_list()
    parts = ["values","verif"]
    fcts = ["selsub"]
    modes = ['scalar']
    create_bench(tb_name,fct_list=fcts,modes=modes,show=True)
