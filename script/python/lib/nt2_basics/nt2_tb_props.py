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


"""Utilities to get nt2 toolbox properties
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from files_utils       import read, exist, write
sys.path.pop(0)

import re
from pprint            import PrettyPrinter
from nt2_modules       import Nt2_modules
from nt2_base_infos    import Nt2_base_infos
from nt2_archis_struct import Nt2_archis_struct
from nt2_tb_struct     import Nt2_tb_struct

class Nt2_tb_props(Nt2_modules,Nt2_tb_struct) :
    """ fct properties of existing nt2 toolboxes"""
    def __init__(self, tb_name) :
        Nt2_modules.__init__(self)
        Nt2_tb_struct.__init__(self)
        self.__tb_name = tb_name
        self.__md_path = os.path.join(self.get_nt2_path(),'modules',self.demangle(tb_name))
        self.__tb_style = self.get_module_style(tb_name)

    def get_tb_name(self)     : return self.__tb_name
    def get_md_path(self)     : return self.__md_path
    def get_tb_path(self)     :
        return os.path.join(self.get_md_path(),'include',self.demangle(self.get_tb_name(),'toolbox'))
    def get_tb_style(self)    : return self.__tb_style
    def get_def_path(self)    : return os.path.join(self.get_tb_path(),'functions')
    def get_const_path(self)    : return os.path.join(self.get_tb_path(),'constants')
    def get_redef_path(self)  : return os.path.join(self.get_tb_path(),'include','functions')
    def get_bench_path(self)  : return os.path.join(self.get_md_path(),'bench')
    def get_exhaustive_path(self)  : return os.path.join(self.get_md_path(),'exhaustive')
    def get_unit_path(self,part)   : return os.path.join(self.get_md_path(),part)
    def get_doc_path(self)    : return os.path.join(self.get_md_path(),'doc')
    def get_include_path(self): return os.path.join(self.get_md_path(),'include')

    def get_fcts_list(self) :
        l = []
        for name in os.listdir(self.get_doc_path()) :
            if name[-3:]=='.py' :
                h = name[:-3]
                l.append(h)
        return sorted(l)

    def demangle(self,name,insert=None,i=0) :
        ll = name.split('.')
 ##       print("avant %s"% ll)
 ##       print("ins %s"%insert)
        if insert is not None : ll.insert(-1,insert)
 ##       print(i)
 ##       print ("demangle %s "%ll)
        if len(ll) == 2 : ll.insert(0,'nt2')
        r = ''
        for l in ll : r = os.path.join(r,l)
 ##       print('r %s'%r)
        return r

    def __str__(self) :
        r  = "tbi.get_tb_path():     %s" % tbi.get_tb_path    ()
        r += "\ntbi.get_tb_name():     %s" % tbi.get_tb_name    ()
        r += "\ntbi.get_tb_style():    %s" % tbi.get_tb_style   ()
        r += "\ntbi.get_def_path():    %s" % tbi.get_def_path   ()
        r += "\ntbi.get_bench_path():  %s" % tbi.get_bench_path ()
        r += "\ntbi.get_unit_path('cover'):   %s" % tbi.get_unit_path  ('cover')
        r += "\ntbi.get_unit_path('unit') :   %s" % tbi.get_unit_path  ('unit')
        r += "\ntbi.get_doc_path():    %s" % tbi.get_doc_path   ()
        r += "\ntbi.get_fcts_list():  [ \n"
        for f in tbi.get_fcts_list() :  r += " "*5+f+'\n'
        r += " "*5+"]\n"
        return r

    def what_are_we_looking_for(self,fct_name,verbose=False) :
        "returns the files we are looking for, for a functor in a module"
        tb_name = self.get_tb_name()
        if verbose :
            print("for the '%s' module and functor '%s' \nthe following files are looked for,"% (tb_name,fct_name))
            print("from nt2 root:")
        r = []
        for f in self.get_rel_tb_fcts_files(tb_name,fct_name) :
            if re.match("doc|bench|unit",f) :
                r += os.path.normpath(os.path.join(tb_name,f))
                if verbose : print("  %s"% os.path.normpath(os.path.join(tb_name,f)))
            else :
                r += os.path.normpath(os.path.join(self.get_tb_from_md_path(),f))
                if verbose : print("  %s"% os.path.normpath(os.path.join(self.get_tb_from_md_path(),f)))
        return r

    @classmethod
    def __print_cond(self,head,mes) :
        if not head :
            print(mes)
            return True
        return head

    def who_is_here(self,fct_name,verbose=False) :
        """returns the files already present for a functor in a module"""
        tb_name = self.get_tb_name()
        head = False
        mes = ("for the '%s' module and functor '%s' \nthe following files exist:"% (tb_name,fct_name))
        r = []
        for f in self.get_rel_tb_fcts_files(tb_name,fct_name) :
            if re.match("doc|bench|unit",f) :
                if exist(os.path.join(self.get_md_path(),f)) :
                    r += os.path.abspath(os.path.join(self.get_md_path(),f))
                    if verbose :
                        head = self.__print_cond(head,mes)
                        print("  %s"% os.path.abspath(os.path.join(self.get_md_path(),f)))
            else :
                if exist(os.path.join(self.get_tb_path(),f)) :
                    r +=  os.path.abspath(os.path.join(self.get_tb_path(),f))
                    if verbose :
                        head = self.__print_cond(head,mes)
                        print("  %s"% os.path.abspath(os.path.join(self.get_tb_path(),f)))
        if (not head) and verbose : print("for the '%s' module and functor '%s', no files are defined"% (tb_name,fct_name))

    def who_is_missing(self,fct_name,verbose=False) :
        """returns what files are potentially missing for a functor in a module"""
        tb_name = self.get_tb_name()
        head = False
        mes = "for the '%s' module and functor '%s' \nthe following files are not defined:"% (tb_name,fct_name)
        r = []
        for f in self.get_rel_tb_fcts_files(tb_name,fct_name) :
            if re.match("doc|bench|unit",f) :
                if not exist(os.path.join(self.get_md_path(),f)) :
                    r += os.path.abspath(os.path.join(self.get_md_path(),f))
                    if verbose :
                        head = self.__print_cond(head,mes)
                        print("  %s"% os.path.abspath(os.path.join(self.get_md_path(),f)))
            else :
                if not exist(os.path.join(self.get_tb_path(),f)) :
                    r +=  os.path.abspath(os.path.join(self.get_tb_path(),f))
                    if verbose :
                        head = self.__print_cond(head,mes)
                        print("  %s"% os.path.abspath(os.path.join(self.get_tb_path(),f)))
        if (not head) and verbose : print("for the '%s' module and functor '%s', no files are missing"% (tb_name,fct_name))


if __name__ == "__main__" :
    tbi = Nt2_tb_props("boost.simd.arithmetic")
    print(tbi)
##    tbi = Nt2_tb_props("cephes")
##    print(tbi)
##    tbi = Nt2_tb_props("sdk")
##    print(tbi)
##    tbi.what_are_we_looking_for("abs")
##    tbi.who_is_here("abs")
##    tbi.who_is_missing("abs")
