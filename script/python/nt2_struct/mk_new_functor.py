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


"""Utilities to create new style functor implementation
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
import re
import datetime
import shutil
from display_utils import show
from files_utils   import write, exist
from re_list       import sub_list

class Mk_fctor :
    def __init__(self, fct_infos) :
        self.fcti = fct_infos

    def create_stamp(self) :
        author = self.fcti.tbi.nbi. get_author()
        r = [
            "/// Revised by " + author + " the "+datetime.datetime.now().strftime("%d/%m/%Y"), 
            ""
            ]
        return r

    def create_call(self, dispatch):
        mode = self.fcti.get_fct_mode()
        test = re.search("common",mode)
        p1 = "class Extension, " if test else ""
        if test :
            p2 = ",Extension"
        elif mode == "scalar" :
            p2 = ""
        else :
            p2 = ",tag::"+self.fcti.get_fct_archi_spec()+"_"
        p3 = "" if  self.fcti.tbi.get_tb_style() == "sys" else  self.fcti.tbi.get_tb_name()+"::"
        r = [
            "",
            "  /////////////////////////////////////////////////////////////////////////////",
            "  // Implementation when type "+ (
                self.fcti.get_old_fct_dispatch_type() +
                " is " + dispatch),
            "  /////////////////////////////////////////////////////////////////////////////",
            "  template<"+p1+"class Info>",
            "  struct call<" + (p3+self.fcti.get_fct_name() +
                                 "_,tag::"+ self.fcti.get_fct_archi() +
                                 "_(tag::arithmetic_"+p2+")," +
                                 dispatch +
                                 ",Info> : callable"),
            "  {"
            ]
        r += self.fcti.get_result_txt()
        s = self.fcti.get_old_fct_call(dispatch)
        if s is not None :
            if len(s)==1 :
                s = sub_list(" *NT2_FUNCTOR_CALL_EVAL_IF\( *\d *,.*\) *{",
                         "    NT2_FUNCTOR_CALL("+str(self.fcti.get_fct_arity())+"){",s)
                s = sub_list(" *}"," }",s)
            else :   
                 s = sub_list(" *NT2_FUNCTOR_CALL_EVAL_IF\( *\d *,.*\)",
                         "    NT2_FUNCTOR_CALL("+str(self.fcti.get_fct_arity())+")",s)
        else :
            s = self.fcti.get_old_fct_call(None)
        def postfix(d) :    
            c = {"float" : "f","double" : "", "long double" : "l"}
            if d in c.keys() :
                return c[dispatch]
            else :
                return ""
        s = sub_list("cephes_"+self.fcti.get_fct_name(), "cephes_"+self.fcti.get_fct_name()+postfix(dispatch),s)
        r += s
        r += [
            "  };"
            ]
        return r
   
    def create_calls(self) :
        d_on,d_list = self.fcti.get_old_fct_dispatch()
        if len(d_list) != 0 :
            r = []
            for dispatch in d_list :
                r += self.create_call( dispatch)
                r += [""]
        else :
            r =  self.create_call("fundamental_")
        return r

    def compose_new_fctor_txt(self) :
        if self.fcti.is_subsidiary()      : return "is subsisiary"
        if self.fcti.is_already_revised() : return "was already revised " 
        fct_txt =  self.fcti.get_head_up_to_first_call()
        fct_txt += self.create_calls()
        fct_txt += self.fcti.get_footer()
        fct_txt += self.create_stamp()
        return fct_txt

    def show_new_fctor(self) :
        new = self.compose_new_fctor_txt()
        if type(new) is str :
            print "%s %s" % (self.fcti.get_fct_name(),new)
        else :
            print "showing %s" % self.fcti.get_fct_path()
            show(new)

    def save_new_fctor(self) :
        print "making %s" % self.fcti.get_fct_path()
        new = self.compose_new_fctor_txt()
        if type(new) is str :
            print "%s %s" % (self.fcti.get_fct_name(),new)
        else :
            shutil.move(self.fcti.get_fct_path(),re.sub('.hpp','.bak',self.fcti.get_fct_path()))
            write(self.fcti.get_fct_path(),new,True)
            print "done"

    def revert_to_old_fctor(self) :
        if self.fcti.is_already_revised() :
            if self.fcti.no_restore() :
                print "no restore allowed for %s" % self.fcti.get_fct_path()
                return
            bak = re.sub('.hpp','.bak',self.fcti.get_fct_path())
            if exist(bak) :
                print "reverting %s" % self.fcti.get_fct_path()
                shutil.move(bak,self.fcti.get_fct_path())
            else :
                print "no bak file for reverting %s" % self.fcti.get_fct_path()
        else :
            print "file %s is not already revised" % self.fcti.get_fct_path()


if __name__ == "__main__" :
    print __doc__
    from nt2_tb_functors_infos import Fctor_infos
    fi = Fctor_infos("arithmetic","abs","simd/sse","ssse3")
    mf = Mk_fctor(fi)
    print"old================="
    show(fi.get_old_fctor_txt())
    print"new================="
    show(mf.compose_new_fctor_txt())
#    mf.save_new_fctor()
