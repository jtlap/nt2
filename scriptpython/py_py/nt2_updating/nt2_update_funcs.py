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


"""update of def syntax : transitionnal
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"nt2_basics"))
import datetime
import shutil
import re
import string
from datetime                        import datetime
from files_utils                     import write, exist, read
from nt2_base_infos                  import Nt2_base_infos
from pprint                          import PrettyPrinter
from nt2_tb_props                    import Nt2_tb_props
from nt2_fct_props                   import Nt2_fct_props
from nt2_fct_internals               import Nt2_fct_internals
from modify_base                     import Modify_base
sys.path.pop(0)
sys.path.pop(0)

Dispatch_Txt = """  NT2_REGISTER_DISPATCH(%(tb)stag::%(name)s_%(tpl1)s, tag::cpu_,
%(blanks)s  %(list_A)s, 
%(blanks)s  %(tag_list_A)s
%(blanks)s )
"""
    
New_Call = """  template<%(tpl)sclass Dummy>
  struct call<%(tb)stag::%(name)s_%(tpl1)s(%(tag_list)s),
              tag::cpu_, Dummy> : callable""" 


class Nt2_update_scalar_fct(Nt2_fct_props) :
    def __init__(self, tb_name, fct_name) :
        Nt2_fct_props.__init__(self, tb_name, fct_name)

    def duplicate_fct(self) :
        pin = self.get_fct_impl_path('scalar')
        pout = pin+'.old'
        Modify_base.duplicate(pin,pout)

    def restore_fct(self) :
        pout = self.get_fct_impl_path('scalar')
        pin = pout+'.old'
        Modify_base.restore(pin,pout)

    def manual(self,p) :
         return re.search('manually modified','/n'.join(read(p)))
                         
    def modify_fct(self,tryonly='tryonly') :
        """ text is always modified from old one"""
        style = self.get_tb_style()
        fct_name = self.get_fct_name()
        print("modifying fct for %s with style %s"% (fct_name,style))
        new =  self.get_fct_impl_path('scalar')
        old = new+'.old'
        if self.manual(new) :
            print("file \n   %s\nwas manually modified: skipping" % new)
            return
        if not exist(old) : self.duplicate_fct()
        oldtxt = read(old)
        (beg,end)=Nt2_fct_internals.get_header_indices(oldtxt)
        newtxt=oldtxt[beg:end]
        newtxt += Nt2_fct_internals.get_extern_C(oldtxt)
        calls = Nt2_fct_internals.get_calls(oldtxt)
        for c in calls.keys() :
            newtxt += [l.expandtabs(6) for l in self.mk_nw_call(c,calls[c])]
        newtxt += ["","#endif"]               
        newtxt += ['// modified by %s the %s' % (self.get_author(), datetime.now().strftime("%d/%m/%Y"))]
        newtxt = self.replacements(newtxt,'\sNT2_CALL_RETURN_TYPE\(',' NT2_RETURN_TYPE(')
        newtxt = self.replacements(newtxt,'long double_','long_double_')
        newtxt = self.replace('(?i)gsl_specfun::',fct_name,fct_name.lower(),newtxt)
        if tryonly != 'tryonly' :
            write(new,newtxt,False)
        else :
            print("---------------")
            PrettyPrinter().pprint(oldtxt)
            print("===============")
            PrettyPrinter().pprint(newtxt)
            print("===============")

    def replacements(self, txt, orig, rep) :
        return [ re.sub(orig,rep,s) for s in txt]

    def replace(self, prefix,pattern, sub, txt) :
        for i,l in enumerate(txt) :
            if re.search(prefix+pattern,l.lower()) :
                print(l)
                txt[i] = re.sub('(?i)'+pattern,sub,l)
                print(txt[i])
        return txt
    
    def mk_nw_call(self,c,oldcall) :
        arity = int(self.get_fct_arities()[0])
        tb_style = self.get_tb_style()
        fct_name = self.get_fct_name()
        tb_name  = self.get_tb_name()
        tag_list = self.strlist("tag::"+self.tag(c),n=0,sep=",",arity=arity)
        newtxt = oldcall[:4]
        test = re.search(',',oldcall[4])
        tpl = "class Rounding," if test else ""
        tpl1= "<Rounding>"      if test else ""
        newtxt += self.mk_dispatch(c,arity,tpl1)
        newtxt = [s[2:] for s in newtxt]
        newtxt += ["namespace nt2 { namespace ext ", "{"]
        tb = tb_name+'::' if tb_style == 'usr' else ""
        s = New_Call % {'tb' : tb, 'tpl' : tpl, "tpl1": tpl1,
                        'name' : fct_name,'tag_list' : tag_list}
        newtxt += s.split('\n')
        newtxt += oldcall[6:]
        newtxt += ["} }"]
        return [s.rstrip() for s in newtxt]


    def strlist(self,tpl,n=1,sep = ", ",arity=1) :
        s = tpl % (n*(0,))
        tpl =sep+tpl
        for i in range(1,arity) :
            s += tpl % (n*(i,))
        return s
    
    def tag(self,t) :
        if t[-1] == '_' : return t
        if t[-2:] == '_t' : return t[:-1]
        return t+'_' 
    
    def mk_dispatch(self,c,arity,tpl1) :
        fct_name = self.get_fct_name()
        tb_name  = self.get_tb_name()
        tb_style = self.get_tb_style()
        tb = tb_name+'::' if tb_style == 'usr' else ""
        blanks =' '*(len(fct_name)+18)
        rnd = tpl1 if tpl1=="" else "("+tpl1[1:-1]+")"
        list_A = self.strlist("(A%d)",sep="",arity=arity)+rnd
        tag_list_A = self.strlist("("+self.tag(c)+"<A%d>)",sep="",arity=arity)
        s = Dispatch_Txt % {'tb' : tb, 'name' : fct_name, "tpl1": tpl1,
                            'blanks' : blanks,'list_A' : list_A,'tag_list_A' : tag_list_A}
        return s.split('\n')

    def mk_new_call(self,s,c,arity) :
        fct_name = self.get_fct_name()
        tag_list = self.strlist("tag::"+self.tag(c),n=0,sep=",",arity=arity)
        s = New_Call % {'name' : fct_name,'tag_list' : tag_list}
        return s.split('\n')


if __name__ == "__main__" :
    nud = Nt2_update_scalar_fct("crlibm","acospi_rn")
    print("ok")
    nud.modify_fct()
