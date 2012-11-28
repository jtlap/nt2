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
        dirname = self.get_modules_path()
        for p in tb_name.split('.') : dirname =  os.path.join(dirname,p)
        dirname = os.path.join(self.get_modules_path(),dirname)
        filename = os.path.join(dirname,"include","nt2","toolbox",tb_name+'.hpp')
##        if exist(filename) :
##            s = read(filename)
##            pattern = re.compile("^// This toolbox is of (.*) type")
##            for l in s :
##                d1 = re.match(pattern,l)
##                if d1 : return d1.groups()[0]
        filename = os.path.join(dirname,'py_data.py')
        if exist(filename) :
            s = '\n'.join(read(filename))
            exec(s)
            return datas.get('style','usr')
        return 'usr'

    def __get_modules_list(self,styles=None, p=None,l=None) :
        if styles is None : styles = ['sys','usr']
        if isinstance(styles, str) : styles = [styles]
        if l is None : l = []
        if p is None : p = self.get_toolboxes_path()
        for name in os.listdir(p) :
            p1 = os.path.join(p,name)
            if os.path.isdir(p1) :
                filename = os.path.join(p1,'py_data.py')
                if exist(filename) :
                    s = '\n'.join(read(filename))
                    exec(s)
                    prefix = datas.get('prefix',[])
                    if ((datas.get('style','usr') in styles) or
                        ((datas.get('has_submodules',False)) )):
                        if (datas.get('has_submodules',False)) :
                            p2 = p
                            for pr in prefix : p2=os.path.join(p2,pr)
                            self.__get_modules_list(styles,p2,l)
                        else :
                            h = ''
                            for pr in prefix : h +=pr+'.'
                            h += name
                            l.append(h)
        return l

    def get_modules_list(self,styles=None,root='*') :
        l = self.__get_modules_list(styles)
        if '*' == root :
            pass
        elif '_' == root :
            l= [n for n in l if not ('.' in n)]
        else :
            l= [n for n in l if  ('.' in n) and re.match(root,n) ]
        return sorted(list(set(l)))

if __name__ == "__main__" :
    tbi = Nt2_modules()
    print(tbi.get_module_style("arithmetic"))
    print(tbi.get_module_style("boost.simd.arithmetic"))
    print(tbi.get_module_style("fdlibm"))
    print("")
##    md_name = tbi.get_modules_list(['sys'])
##    for md in md_name : print(md)
##    print("")
##    md_name = tbi.get_modules_list(['usr'])
##    for md in md_name : print(md)
##    print("")
##    md_name = tbi.get_modules_list(['usr','sys'])
##    for md in md_name : print(md)
    print("")
    md_name = tbi.get_modules_list(['usr','sys'])
    for md in md_name : print(md)
    print("")
    md_name = tbi.get_modules_list(['usr','sys'],'')
    for md in md_name : print(md)
    print("")
    md_name = tbi.get_modules_list(['usr','sys'],'boost')
    for md in md_name : print(md)
    print("")
    md_name = tbi.get_modules_list(['usr','sys'],['boost','*'])
    for md in md_name : print(md)

