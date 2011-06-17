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


"""Utilities to get nt2 toolboxes 
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
from nt2_base_infos    import Nt2_base_infos

class Nt2_modules(Nt2_base_infos) :##(Nt2_base_infos,Nt2_tb_struct) :
    """ fct properties of existing nt2 toolboxes"""
    def __init__(self) :
        Nt2_base_infos.__init__(self)

    def get_modules_path(self) :
        return os.path.join(self.get_nt2_path(),'modules')

    def get_module_style(self,tb_name) :
        dirname = os.path.join(self.get_modules_path(),tb_name)
        filename = os.path.join(dirname,"include","nt2","toolbox",tb_name+'.hpp')
        if exist(filename) :
            s = read(filename)
            pattern = re.compile("^// This toolbox is of (.*) type")
            for l in s :
                d1 = re.match(pattern,l)
                if d1 : return d1.groups()[0]
  
        filename = os.path.join(dirname,'py_data.py')
        if exist(filename) :
            if re.search("'usr'",' '.join(read(filename))) :
               return 'usr'
            else :
               return 'sys'
        return 'usr'

    def get_modules_list(self,styles=None) :
        if styles is None : styles = ['sys','usr']
        if isinstance(styles, str) : styles = [styles]
        l = []
        p = self.get_toolboxes_path()
        for name in os.listdir(p) :
            p1 = os.path.join(p,name)
            if os.path.isdir(p1) and exist(os.path.join(p1,'py_data.py')):
                if (styles is None) or (self.get_module_style(name) in styles) :
                    h = name
                    l.append(h)
        if "models" in l : l.remove("models")        
        return l


if __name__ == "__main__" :
    tbi = Nt2_modules()
    print(tbi.get_module_style("arithmetic"))
    print(tbi.get_module_style("fdlibm"))
