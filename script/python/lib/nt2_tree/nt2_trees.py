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
from __future__         import print_function


"""Utilities to get nt2 (toolboxes) tree structure
this give toolbox independant informations
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
from files_utils      import read, exist
from iter_utils       import flatten
sys.path.pop(0)

import re
from pprint           import PrettyPrinter

## http://oprofile.sourceforge.net

class Nt2_trees() :
    """ subdirectory structures required by nt2 """
    def __init__(self) : pass

    @classmethod
    def get_Src(cls) :
        Src = {
            "name"      : "src",
            "existence" : "modules",
            "files"     : {"CMakeLists.txt" : "cmakelist3" },
            }
        return Src

    @classmethod
    def get_Test(cls) :
        Test = {
            "name"      : "test",
            "existence" : "always",
            "files"     : { "CmakeLists.txt" : "cmakelist2" },
            }
        return Test
    @classmethod
    def get_Tests(cls) :
        Tests = {
            "name"      : "tests",
            "existence" : "modules",
            "files"     : { "CmakeLists.txt" : "cmakelist1" },
            "childs"    : {
                "scalar" : cls.get_Test(),
                "simd"   : cls.get_Test(),
                }
            }
        return Tests


    @classmethod
    def get_Doc(cls) :
        Doc = {
            "name"      : "doc",
            "files"     : { "$name$.dox" : "dox" },
            "childs"    : {
                "source" :  {"existence" : "always"},
                },
        }
        return Doc

    @classmethod
    def get_Python(cls) :
        Python = {
            "name" : "python",
            "childs"    : {
                "lib" : None ,
                "usr" : None ,
                }
            }
        return Python

    @classmethod
    def get_Scripts(cls) :
        Scripts = {
            "name" : "scripts",
            "childs"    : {
                "python" : cls.get_Python(),
                },
            }
        return Scripts


    @classmethod
    def get_module_tree(cls,recurse,tb_name) :
        Module_tree = {
            "name" : "Module_tree",
            'childs': {
                'bench':    cls.get_Tests(),
                'cmake':    None ,
                'cover':    cls.get_Tests(),
                'doc':      cls.get_Doc,
                'include':  cls.get_Include(recurse,tb_name),
                'src':      cls.get_Src(),
                'unit':     cls.get_Tests(),
                },
            'files':     {
                "CMakeLists.txt" : "cmakelist0",
                "pydata.py"      : "pydata"
                }
            }
        return Module_tree

    @classmethod
    def get_Sys_modules(cls,recurse,tb_name) :
#        print ("recurse %s"%recurse)
        if recurse > 1 :
            recurse -= 1
            Sys_modules = {
                "name" :"sys_modules",
                "childs"    : {
                    "arithmetic":    cls.get_module_tree(recurse,"arithmetic"),
                    "bitwise":       cls.get_module_tree(recurse,"bitwise"),
                    "constant":      cls.get_module_tree(recurse,"constant"),
                    "core":          cls.get_module_tree(recurse,"core"),
                    "exponential":   cls.get_module_tree(recurse,"exponential"),
                    "hyperbolic":    cls.get_module_tree(recurse,"hyperbolic"),
                    "ieee"      :    cls.get_module_tree(recurse,"ieee"),
                    "operator":      cls.get_module_tree(recurse,"operator"),
                    "polynomial":    cls.get_module_tree(recurse,"polynomial"),
                    "predicate":     cls.get_module_tree(recurse,"predicate"),
                    "reduction":     cls.get_module_tree(recurse,"reduction"),
                    "swar":          cls.get_module_tree(recurse,"swar"),
                    "trigonometric": cls.get_module_tree(recurse,"trigonometric"),
                    },
                }
        else :
            Sys_modules = {
                "name" :"sys_modules",
##                "childs" : {
##                    "function" : None,
##                    "include"  : None,
##                    }
                }
        return Sys_modules

    @classmethod
    def get_Include(cls,recurse,tb_name) :
        Include = {
            "name" : "include",
            "childs" : {
                "nt2 " : {
                    "name" : "nt2",
                    "childs" : {
                        "toolbox" : {
                            "name" : "toolbox",
                            "childs" : {
                                tb_name : cls.get_Sys_modules(recurse,tb_name),
                                }
                            }
                        }
                    }
                }
            }
        return Include

    @classmethod
    def get_Modules(cls) :
        Modules = {
            "name"      : "modules",
            "childs"    : cls.get_Sys_modules(),
            }
        return Modules

    @classmethod
    def get_Nt2_tree(cls) :
        Nt2_tree = {
            "name": "nt2",
            "childs" : {
                'build':    None ,
                'cmake':    None ,
                'doc':      cls.get_Doc(),
                'modules':  cls.get_Sys_modules(2,"nt2"),
                'sandbox':  None ,
                'script':   cls.get_Scripts(),
                },
            "files" : {
                "LICENSE":         {"template" : None },
                "CmakeLists.txt":  {"template" : None },
                "Readme.rst":      {"template" : None },
                }
            }
        return Nt2_tree


    @classmethod
    def print_nt2_dev_pathes(self, d, name) :
        level=1
        prev = ""
#      print(d.get("name",prev))
        print(name+'/')
        def print_next(d,level) :
            if isinstance(d, dict ) :
#                print(d.get("name",prev))
                blks = "  "*level
##                for f in sorted(d.keys()) :
##                    print('--> %s'%f)
                d1 = d.get("childs",None)
                if isinstance(d1, dict ) :
#                    print(d1)
                    for child in sorted(d1.keys()) :
                        print("%s%s/"%(blks,child))
                        if isinstance(d1.get(child,None),dict ) :
                            d2 = d1.get(child,None)
                            if d2.get("childs",None) is not None :
                                print_next(d2,level+1)
        print_next(d,level)
if __name__ == "__main__" :
    Nt2_trees.print_nt2_dev_pathes(Nt2_trees.get_Nt2_tree(),"nt2")
    Nt2_trees.print_nt2_dev_pathes(Nt2_trees.get_module_tree(1,"zorglub"),"zorglub")

