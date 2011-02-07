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


"""Utilities to get nt2 base structure
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

import re
from pprint           import PrettyPrinter
from files_utils      import read, exist
from iter_utils       import flatten

class Nt2_base_struct() :
    """ subdirectory structure required by nt2 """
    Required_directories = ['','benchmark','unit', 'doc', 'examples','src','lib','sandbox','script','include']
    Required_base_tree = {
        'benchmark'   : ['operators'],
        'unit'        : ['sdk'],
        'doc'         : ['source'],
        'examples'    : ['sdk','core'],
        'src'         : ['sdk','core'],
        'lib'         : ['Release'],
        'sandbox'     : [],
        'script'      : ['py_nt2_utils'],
        'include'     : ['->nt2'],
        }
    Required_nt2_tree = {
        ""            : [],
        "core"        : ['timing'],
        "extension"   : [],
        "include"     : ['functions'],
        "sdk"         : ['concept','config','constant','details','dsl','error','functor','memory','meta','option','simd','unit',],
        "toolbox"     : ["->$tb_name$*"],       
    }
    Required_nt2_unique_files = {
        ""            : ['nt2.hpp'],
        "core"        : ['timing'],
        "extension"   : [],
        "include"     : ['functions'],
        "sdk"         : [],
        "toolbox"     : ["->$tb_name$s"],
    }
    """
    ???               
    """
    
    def __init__(self,author='jt') :
        self.__author = author
    
    @classmethod
    def get_nt2_rel_tb_path(self, to = '') : return self.grtp(to)

    @classmethod
    def get_rel_tb_tree(cls, root=None) :
        if type(root) is str :
            if root == "function" :
                a = [os.path.join(root,arch) for arch in cls.get_rel_archis_tree()]
            elif not (root in  cls.Required_base_tree) :
                return []
            else :
                a = [os.path.join(root,arch) for arch in cls.Required_base_tree[root] ]
            return [root]+a
        else :
            if root is None : root = cls.Required_base_tree
            z = [ cls.get_rel_tb_tree(r) for r in root]
            return list(flatten(z))

   
    @classmethod    
    def grtp(cls, to = '',mode='') :
        """ return realative path from the toolbox to 'to' and 'mode'
        to can be 'function', 'bench', 'unit', 'doc', 'src', 'include'
        and for some mode can be 'scalar' or 'simd'
        """
        if to =='' : return ''
        if mode == '' : return to
        return os.path.join(to,mode)
    


if __name__ == "__main__" :
    PrettyPrinter().pprint(Nt2_base_struct.get_rel_tb_tree("zorglub"))
    PrettyPrinter().pprint(Nt2_base_struct.get_rel_tb_tree())
sys.path.pop(0)
