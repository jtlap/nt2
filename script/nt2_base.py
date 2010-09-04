#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""nt2 tree
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import os
import sys
import re
from mylogging  import Mylogging
from nt2_env    import nt2_dir
from archi      import Sse, Vmx

class Nt2 :
    """ This class contains info about the nt2
    directory tree"""
    Std_paths_from_nt2      = {
        'toolbox' : "nt2/toolbox/",
        'core'    : "nt2/core/",
        'sdk'     : "nt2/sdk/"
        }
    Std_arbo = [
        ["include",
         "src",   
         {"doc" : ["source"] },
         {"unit": ["scalar"] },
         {"benchmark": ["simd"] },
         {"function" :
          ["scalar",
           {"simd"   :
            ["common",
             {"vmx" : Vmx.Variants.keys() },
             {"sse" : Sse.Variants.keys() }
             ]
            }
           ]
          }
         ]
        ]
                                                                         
    Std_actions = {
        "benchmark": ["benchmark",     'std',  'benchmark'               ],     
        "doc"      : ["doc",           'std',  'doc/source/'             ],    
        "include"  : ["include",       'std',  'include/'                ],          
        "function" : ["define",        'std',  'function/'               ],                   
        "scalar"   : ["scalar",        'std',  'function/scalar/'        ],
        "common"   : ["common",        'std',  'function/simd/common/'   ],     
        "vmx"      : ["hierarchy",     'hie',  'function/simd/vmx/', Vmx ],
        "sse"      : ["hierarchy",     'hie',  'function/simd/sse/', Sse ]
        }
    def __init__(self,
                 mode='toolbox',
                 arbo=None,
                 actions = None) :
        self.logger = Mylogging("nt2.nt2_base.Nt2")
        self.__mode = mode
        self.__pathfnt2 = self.path_from_nt2(self.__mode)
        self.__actions = (Nt2.Std_actions if actions is None else actions)
        self.__arbo    = (Nt2.Std_arbo if arbo is None else arbo)
        self.__path2nt2=nt2_dir()

    def get_path_from_nt2(self) : return self.__pathfnt2
    def get_path_to_nt2  (self) : return self.__path2nt2
    def get_pathfnt2(self) : return self.__pathfnt2
    def get_path2nt2(self) : return self.__path2nt2

    def path_from_nt2(self,mode) :
        return (Nt2.Std_paths_from_nt2[mode]
                         if (mode in Nt2.Std_paths_from_nt2)
                         else 'nt2/'+mode+'/')
    def absolute_path_to_mode    (self,mode = None) :
        if mode is None : mode = self.__mode
        return os.path.join(self.__path2nt2,
                            self.path_from_nt2(mode))
    def get_mode(self) : return self.__mode
    def get_arbo(self) : return self.__arbo
    def get_actions(self) : return self.__actions


    
if __name__ == "__main__":
    Mylogging.set_level('INFO')
    nt2 = Nt2()
    print "nt2.get_path_from_nt2     %s" %nt2.get_path_from_nt2()
    print "nt2.get_path_to_nt2       %s" %nt2.get_path_to_nt2()
    print "nt2.absolute_path_to_mode %s" %nt2.absolute_path_to_mode()
    print "nt2.absolute_path_to_mode('zut')  %s" %nt2.absolute_path_to_mode('zut')
    print "nt2.path_from_nt2('zut')    %s" %nt2.path_from_nt2('zut')


