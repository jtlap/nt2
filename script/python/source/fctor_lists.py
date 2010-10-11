#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

"""Tools for seeing what are the existing functor in an nt2 existing Toolbox
   to an existing nt2 toolbox
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import re
import string
from fctor import Functor
from mylogging     import Mylogging
from file_utils    import read
from list_utils    import show

class Fctr_list(Functor) :
    """get functor list according criterias"""
    def __init__(self, tool_box_name) :
        Functor.__init__(self, tool_box_name,'check')
        self.logger = Mylogging("nt2.fctor_lists.Fctr_list")
        st = self.check_tbox()  
        if not st :
            self.logger.error(
                "\ntoolbox %s does not exists\n" % self.get_tb_name() +
                "in path: %s\n" % self.get_tb_abs_path()
                )

    def get_functors_rel_path(self) :
        a = os.path.join(self.get_tb_abs_path(),self.get_tb_name()+'.hpp')
        s = read(a)
        r = []
        for l in s :
            m= re.search('\#include <(.*)>',l)
            if m :
                r.append(m.groups()[0])
        return r

    def get_functors_abs_path(self) :
        s = self.get_functors_rel_path()
        a = self.get_path_to_nt2()
        r = []
        for l in s :
            r.append(os.path.join(a,l))
        return r
    
    def get_functors_names(self) :
        s = self.get_functors_rel_path()
        r = []
        for l in s :
            r.append(l.split('/')[-1])
        return r

    def get_functors_datas(self) :
        pathes = self.get_functors_abs_path()
        dr = {}
        for p in pathes :
            d= {}
            lp = p.split('/')
            lp[-2]= 'function'
            name = lp[-1][:-4]
            s = read('/'.join(lp))
            r = []
            for l in s :
                m= re.search('([0-9]+)\) *$',l)
                if m : r.append(int(m.groups()[0]))
            d["arity"]=r
            dr[name]=d    
        return dr   
            
if __name__ == "__main__":
    from list_utils import show
    Mylogging.set_level('ERROR')
    tb = Fctr_list("pipo1")
    show(tb.get_functors_rel_path())
    show(tb.get_functors_abs_path())
    show(tb.get_functors_names())
    show(tb.get_functors_datas())
     
