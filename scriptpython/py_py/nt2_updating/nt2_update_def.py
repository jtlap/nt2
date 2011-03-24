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

  

class Nt2_update_def(Nt2_fct_props) :
    def __init__(self, tb_name, fct_name) :
        Nt2_fct_props.__init__(self, tb_name, fct_name)
        self.__oldtxt = self.get_fct_def_text()

    def duplicate_def(self) :
        pin = self.get_fct_def_path()
        pout = pin+'.old'
        Modify_base.duplicate(pin,pout)

    def restore_def(self) :
        pout = self.get_fct_def_path()
        pin = pout+'.old'
        Modify_base.restore(pin,pout)

    def deplace(self, pattern, txt) :
        for i,l in enumerate(txt) :
            if re.match(pattern,l) :
                txt[i],txt[i+1]=txt[i+1],txt[i][2:]
                return txt
        return txt    

    def replace(self, prefix,pattern, sub, txt) :
        for i,l in enumerate(txt) :
            if re.search(prefix+pattern,l.lower()) :
                print(l)
                txt[i] = re.sub('(?i)'+pattern,sub,l)
                print(txt[i])
        return txt
                
    def modify_def(self, tryonly='tryonly') :
        """ text is always modified from old one"""
        style = self.get_tb_style()
        fct_name = self.get_fct_name()
        print("modifying def for %s with style %s"% (fct_name,style))
        new =  self.get_fct_def_path()
        old = new+'.old'
        if not exist(old) : self.duplicate_def()
        oldtxt = read(old)
#        PrettyPrinter().pprint(oldtxt)
        s = '\n'.join(oldtxt)
        s = re.sub('\t','  ',s)
        if style == 'sys' :
            s = re.sub('functors','tag',s)
        else :
            pattern = 'namespace %s' % self.get_tb_name()
            s = re.sub(pattern,pattern+' { namespace tag',s)
            pattern = '%s::'%self.get_tb_name()
            s = re.sub(pattern,pattern+'tag::',s)
            s = re.sub("(}\s*})","}\n  } }",s)
#            print("===========================")
        newtxt = s.split('\n')
        if self.get_tb_style()=='usr' :
            newtxt = self.deplace("\s*NT2_FUNCTION_IMPLEMENTATION.*",newtxt)
            newtxt = self.deplace("\s*NT2_CRLIBM_FUNCTION_IMPLEMENTATION.*",newtxt)
            newtxt = self.replace('(?i)(:| )',fct_name,fct_name.lower(),newtxt)
        newtxt += ['// modified by %s the %s' % (self.get_author(), datetime.now().strftime("%d/%m/%Y"))]
        if tryonly != 'tryonly' :
            write(new,newtxt,False)
        else :
            print("---------------------------")
            PrettyPrinter().pprint(oldtxt)
            print("===========================")
            PrettyPrinter().pprint(newtxt)
            print("===========================")
            
if __name__ == "__main__" :
    nud = Nt2_update_def("gsl_specfun","gsl_sf_bessel_i0_scaled")
    print("ok")
##    nud.duplicate_def()
##    nud.restore_def()
    nud.modify_def()
