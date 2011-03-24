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


"""base for generation of a functor unit tests
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
from nt2_fct_props                   import Nt2_fct_props


class Base_gen(Nt2_fct_props) :
    def __init__(self, tb_name, fct_name, fct_mode) :
        Nt2_fct_props.__init__(self,tb_name,fct_name)
        self.dl = self.get_fct_dict_list()
        self.__fct_mode = fct_mode

    def get_fct_mode(self) :
        return self.__fct_mode
    def set_fct_mode(self, mode) :
        self.__fct_mode = mode
        return self.__fct_mode
        
    def get_fct_unit_path(self,mode = None)  :
        if mode is None : mode =self.get_fct_mode()
        return os.path.join(self.get_abs_path('toolbox'),
                            self.get_tb_name(),'unit',
                            mode,
                            self.get_fct_name()+'.cpp')

    def recover(self,st,d,default) :
        return d.get(st,default)
    
    def recover_info(self,st,typ,d,extra_def=None) :
        dd = d.get(st, None)
        if dd is None :
            return extra_def
        elif type(dd) is str :
            return dd
        elif dd is  None :
            return None
        else :
            return dd.get(typ, dd.get("default", None ))


    def create_unit_txt_part(self,tpl,prepare,d={},typ="",i=None) :
        """prepare prototype is    def __prepare(self,s,typ,d) : ...
        """
        r = []
        for s in tpl :
            if "$" in s :
                g = prepare(s,typ,d,i)
                if type(g) is str :
                    r.append(g)
                else :
                    r+=g
            else :
                r.append(s)
        return r

if __name__ == "__main__" :
    print __doc__
    bg = Base_gen("exponential",'pipo','scalar')
    print 'After: bg= Base_gen("exponential","pipo","scalar")'
    print "bg.get_fct_name() = %s"%bg.get_fct_name()
    print "bg.get_fct_mode() = %s"%bg.get_fct_mode()
    print "bg.get_fct_unit_path()         = %s"%bg.get_fct_unit_path()
    print "bg.get_fct_unit_path('scalar') = %s"%bg.get_fct_unit_path('scalar')
    print "bg.get_fct_unit_path('simd')   = %s"%bg.get_fct_unit_path('simd')
sys.path.pop(0)
sys.path.pop(0)
