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


"""update of units syntax : transitionnal
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

Dispatch_Txt = """  NT2_REGISTER_DISPATCH(tag::%(name)s%(tpl1)s_, tag::cpu_,
%(blanks)s  %(list_A)s, 
%(blanks)s  %(tag_list_A)s
%(blanks)s )
"""
    
New_Call = """  template<%(tpl)sclass Dummy>
  struct call<tag::%(name)s_%(tpl1)s(%(tag_list)s),
              tag::cpu_, Dummy> : callable""" 


class Nt2_update_scalar_unit(Nt2_fct_props) :
    def __init__(self, tb_name, fct_name) :
        Nt2_fct_props.__init__(self, tb_name, fct_name)

    def duplicate_unit(self) :
        pin = self.get_fct_unit_path('scalar')
        pout = pin+'.old'
        Modify_base.duplicate(pin,pout)

    def restore_unit(self) :
        pout = self.get_fct_unit_path('scalar')
        pin = pout+'.old'
        Modify_base.restore(pin,pout)

    def modify_unit(self,tryonly='tryonly') :
        """ text is always modified from old one"""
        style = self.get_tb_style()
        tb_name = self.get_tb_name()
        fct_name = self.get_fct_name()
        print("modifying fct for %s with style %s"% (self.get_fct_name(),style))
        new =  self.get_fct_unit_path('scalar')
        old = new+'.old'
        if not exist(new) :
            print("%s does not exist" % new)
            return
        if not exist(old) : self.duplicate_unit()
        oldtxt = read(old)
        newtxt = self.replacements(oldtxt,'\t','      ')
        pattern = ('nt2::functors' if style  =='sys' else 'nt2::'+tb_name)
        rep     = ('nt2::tag'      if style  =='sys' else pattern+'::tag')
        pattern = pattern+'::'+fct_name+'_'
        rep = rep + '::'+fct_name+'_'
        newtxt = self.replacements(newtxt,pattern,rep)
            
##        newtxt = self.replacements(oldtxt,'\sNT2_CALL_RETURN_TYPE\(',' NT2_RETURN_TYPE(')
        if tryonly != 'tryonly' :
            write(new,newtxt,False)
        else :
            print("===============")
            PrettyPrinter().pprint(newtxt)
            print("===============")

    def replacements(self, txt, orig, rep) :
        return [ re.sub(orig,rep,s) for s in txt]
    

if __name__ == "__main__" :
    nud = Nt2_update_scalar_unit("cephes","acos")
    print("ok")
    nud.modify_unit()#"vas-y")
