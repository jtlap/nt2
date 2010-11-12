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


"""User utility to suppress simd def in usr toolboxes
   usage:
           toolbox_list.py

   
"""

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'../source'))

import sys
from file_utils import read, write,exist
from mylogging  import Mylogging
from list_utils import show

class Toolboxes :
    def __init__(self) :
        self.__path   = '/home/jt/DevC++/dev_lasmea/github/nt2/include/nt2/toolbox'
        self.__dictio = self.get_fctors_dict()
        
    def get_tb_name_list (self)   : return self.__tb_name
    def get_path(self)  : return self.__path
    def get_dictio (self)  : return self.__dictio
    def get_fctors_dict(self) :
        l = {}
        p0 = self.get_path()
        for name in os.listdir(p0) :
            if name[-4:]=='.hpp' :
                h = name[:-4]
                p = os.path.join(p0,h+'/py_data.py')
                if exist(p) :
                    s = ' '.join(read(p))
                    l[h] ='usr' if s.find('usr') > 0 else 'sys' 
        return l

    def get_usr_tb_list(self) :
         return [l for l in self.__dictio.keys() if self.__dictio[l]=='usr']
    def get_sys_tb_list(self) :
         return [l for l in self.__dictio.keys() if self.__dictio[l]=='sys']


if __name__ == "__main__" :
    Mylogging.set_level('CRITICAL')
    ts =Toolboxes()
#    show(ts.get_fctors_dict)
    show(ts.get_usr_tb_list())
    print "------------"
    show(ts.get_sys_tb_list())
    
sys.path.pop(0)
           
       

