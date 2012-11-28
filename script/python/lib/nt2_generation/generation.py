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


"""generation of an exhaustive test unit
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_generation"))
from py_doc        import Py_doc
from unit_base_gen import Base_gen
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from substitute_utils import Substitute
from files_utils      import write,exist
from add_line         import Add_line
sys.path.pop(0)

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_modules                     import Nt2_modules
sys.path.pop(0)

from pprint   import PrettyPrinter
import re
import datetime

class Gen(Py_doc,Substitute) :
    def __init__(self, base_gen) :
        Py_doc.__init__(self,bg=base_gen,arity=1)
        self.name    = self.bg.get_fct_name()
        self.tb_name = self.bg.get_tb_name()
        self.mode    = self.bg.get_fct_mode()
        self.nfp =  Nt2_fct_props(self.tb_name,self.name,self.mode)
        self.txts    = self.tpl[self.mode]
        self.types   = self.get_types()
        self.collect_py_doc_global_data()

    def collect_py_doc_global_data(self) :
        self.du      = self.d.get("unit",{})

    def gen_global_header(self) :
        r = self.replace(self.txts['global_header_txt'])
        return r

    def gen_main_func(self) :
        r = self.replace(self.txts['main_beg_txt'])
        for self.typ in self.types :
            self.collect_py_doc_typ_data()
            r+=self.replace('\n  //place your test call for $typ$ here')
        r+='\n'
        r+=(self.replace(self.txts['main_end_txt']))
        return r

    def gen_test_func_forwarding(self) :
        r = self.replace(self.txts['test_func_forwarding_txt'])
        return r

    def gen_test_func(self,typ) :
        self.typ = typ
        self.collect_py_doc_typ_data()
        r = self.replace(self.txts['test_func_typ_txt'])
        return r

    def gen_inclusions(self) :
        r=''
        for self.typ in self.types :
            path =  self.get_fct_exhaustive_include_path(self.mode,self.typ)
            p = self.reduce_path(path)
            r += '#include <'+p+'>\n'
        return r

    def gen_test_func_guard_begin(self,path) :
        guard = self.make_guard(path)
        r = '#ifndef '+guard+'\n'+'#define '+guard
        return r

    def gen_test_func_guard_end(self) :
        r = '\n#endif'
        return r

    def make_guard(self,path,token='nt2') :
        p = path.split(os.sep)
        for i,part in enumerate(p) :
            if part == token :
                index = i
                break
        p = '_'.join(p[i:])
        return p.upper().replace('.','_')

    def reduce_path(self,path,token='nt2') :
        p = path.split(os.sep)
        for i,part in enumerate(p) :
            if part == token :
                index = i
                break
        p1 = p[i:]
        p1 = '/'.join(p1)
        return p1

    def gen_include_file(self,path,typ) :
        r = self.gen_test_func_guard_begin(path)
        r+='\n\n'
        r+= self.gen_test_func_forwarding()
        r+='\n\n'
        r+= self.gen_test_func(typ)
        r+='\n\n'
        r+= self.gen_test_func_guard_end()
        r+='\n'
        return r


    def gen_main_file(self) :
        r = self.gen_global_header()
        r+='\n\n'
        r+= self.gen_inclusions()
        r+='\n\n'
        r+= self.gen_main_func()
        r+='\n'
        return r


    def write_file(self,p,txt,
                   show=True,
                   wr=False,
                   check=True,
                   backup=True) :
        txt = txt.split('\n')
        just ="Just"
        if wr :
            just = "Also"
            if backup and exist(p) :
                i = 1;
                while True :
                    pi = p+'.'+str(i)+'.bak'
                    if not(exist(pi)) : break
                    i += 1
                    print("backing to %s"% pi)
                    shutil.copy(p,pi)
            print "writing to %s"%p
            write(p,txt,check)
            if p[-4:]=='.cpp' :
                p1 = os.path.join(os.path.split(p)[0],'CMakeLists.txt')
                addline=Add_line(p1,self.name)
                addline.update_file("SET\( *SOURCES")
        if show :
            print("%s showing text of %s for %s-test"% (just,os.path.split(p)[1],self.mode))
            print("<"+"="*40)
            PrettyPrinter().pprint(txt)
            print("="*40+">")
