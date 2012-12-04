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


"""exhaustive test generation for a functor
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2011    $"
__copyright__ = "Lapreste Jean-thierry"
__license__   = "Boost Software License, Version 1.0"

import os
import sys
import re
import shutil
from pprint                          import PrettyPrinter

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from display_utils                   import show
from files_utils                     import write, exist
from add_line                        import Add_line
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_modules                     import Nt2_modules
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from unit_base_gen                   import Base_gen
sys.path.pop(0)

from exhaustive_gen                       import Exhaustive_gen



def create_one_exhaustive(tb_name,
                          fct_name,
                          mode = 'simd') :
    print("tb %s -> fct -> %s with %s mode"%(tb_name,fct_name,mode))
    bg = Base_gen(tb_name,fct_name,mode)

##    print(bg.get_module_style(tb_name))
    bbg =  Exhaustive_gen(bg)
    return bbg.get_gen_result()

def write_exhaustive(tb_name,fct_name,mode,s,check=False,backup=True) :
    nfp = Nt2_fct_props(tb_name,fct_name,mode)
    print("mode %s"%mode)
    p = nfp.get_fct_exhaustive_path(mode)
    print ('p = %s'%p)
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
    p1 = os.path.join(os.path.split(p)[0],'CMakeLists.txt')
    addline=Add_line(p1,fct_name)
    addline.update_file("SET\( *SOURCES")

def create_exhaustive(tb_name,
                      fct_names,
                      modes = ['simd'],
                      show=True,
                      write_files=False,
                      check_on_write=True,
                      backup_on_write=True) :
    bg = Nt2_modules()
    if isinstance(fct_names,str) : fct_names = [fct_names]
    for fct_name in fct_names :
        for mode in modes :
            r= create_one_exhaustive(tb_name,fct_name, mode=mode)
        if r is None :
            print('error for %s' % fct)
        elif len(r)==0 :
            print('no regeneration possible for %s %s-tests, please do it manually' % (fct,mode))
        else :
            just = "just" if show and not write_files else ""
            if show :
                print("%s showing text of %s.cpp for %s-test"% (just,fct_name,mode))
                print("<"+"="*40)
                PrettyPrinter().pprint(r)
                print("="*40+">")
            if write_files :
                print("writing text of %s.cpp for %s-test"% (fct_name,mode))
                write_exhaustive(tb_name,fct_name,mode,r,
                                 check=check_on_write,
                                 backup=backup_on_write)


if __name__ == "__main__" :
    tb_name = "trigonometric"
    fct_name = 'sin'
    mode = 'simd'
    create_exhaustive(tb_name,fct_name,write_files='False')
