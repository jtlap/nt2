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


"""Utilities to get nt2 toolbox properties 
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
from pprint            import PrettyPrinter
from files_utils       import read, exist, write
from nt2_base_infos    import Nt2_base_infos
from nt2_archis_struct import Nt2_archis_struct
from nt2_tb_struct     import Nt2_tb_struct

class Nt2_tb_props(Nt2_base_infos,Nt2_tb_struct) :
    """ fct properties of existing nt2 toolboxes"""
    def __init__(self, tb_name) :
        Nt2_base_infos.__init__(self)
        Nt2_tb_struct.__init__(self)
        self.__tb_name = tb_name
        self.__tb_path = os.path.join(self.get_nt2_path(),'nt2/toolbox',tb_name)
        self.__tb_style = self. __read_style()
        
    def get_tb_path(self)     : return self.__tb_path 
    def get_tb_name(self)     : return self.__tb_name
    def get_tb_style( self)   : return self.__tb_style
    def get_def_path(self)    : return os.path.join(self.__tb_path,'function')
    def get_bench_path(self)  : return os.path.join(self.__tb_path,'bench')
    def get_unit_path(self)   : return os.path.join(self.__tb_path,'unit')
    def get_doc_path(self)    : return os.path.join(self.__tb_path,'doc')
    def get_include_path(self): return os.path.join(self.__tb_path,'include')

    def get_fcts_list(self) :
        l = []
        for name in os.listdir(self.get_def_path()) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                l.append(h)
        return l

    def __read_style(self) :
        dirname = self.get_tb_path()
        filename = dirname+'.hpp'
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

        self.__tb_style = 'usr'
        return 'usr'
    
    def __str__(self) :
        r =  "tbi.get_tb_path():     %s" % tbi.get_tb_path    ()    
        r += "\ntbi.get_tb_name():     %s" % tbi.get_tb_name    ()    
        r += "\ntbi.get_tb_style():    %s" % tbi.get_tb_style   ()  
        r += "\ntbi.get_def_path():    %s" % tbi.get_def_path   ()   
        r += "\ntbi.get_bench_path():  %s" % tbi.get_bench_path () 
        r += "\ntbi.get_unit_path():   %s" % tbi.get_unit_path  ()  
        r += "\ntbi.get_doc_path():    %s" % tbi.get_doc_path   ()   
        r += "\ntbi.get_fcts_list():   %s" % tbi.get_fcts_list()
        r += "\n"
        return r
    
if __name__ == "__main__" :
    tbi = Nt2_tb_props("arithmetic")   
    print(tbi)
    tbi = Nt2_tb_props("cephes")   
    print(tbi)

sys.path.pop(0)
