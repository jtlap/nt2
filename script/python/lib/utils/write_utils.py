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


"""conditionnaly write files with possible backups
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
from display_utils                   import show
from files_utils                     import write, exist, read
import re
import shutil
from pprint                          import PrettyPrinter

class Write_file(object) :
    def __init__(self,show=True,
                 write_files=False,
                 check_on_write=True,
                 backup_on_write=True,
                 verbose=False) :
        self.show=show
        self.write_files=write_files
        self.check_on_write=check_on_write
        self.backup_on_write=backup_on_write
        self.verbose=True or verbose

    def test_immutable(self) :
        s= '\n'.join(read(p),)
        return s.find('//COMMENTED') != -1

    def write(self,p,name,txt) :
        if self.show : show(txt)
        self.p =p
        self.name = name
        self.txt = txt
        if isinstance(p,str) and exist(self.p) :
##            if self.verbose : print ('path = %s'%self.p)
            tp = os.path.join(self.p,self.name)
            if exist(tp) :
                if not self.write_files :
                    return False
            if self.backup_on_write and exist(tp) :
                if self.verbose : print("backing up %s" %name)
                i = 1;
                while True :
                    tpi = tp+'.'+str(i)+'.bak'
                    if not(exist(tpi)) : break
                    i += 1
                if self.verbose : print("to %s"% tpi)
                shutil.copy(tp,tpi)
            elif not self.write_files :
                print "%s is not written"%tp
                return False
            if self.verbose : print "writing to %s"%tp
            if write(tp,self.txt,self.check_on_write) :
                print "%s is written"%tp
                return True;
        elif self.verbose and  isinstance(p,str) :
            print("%s directory\n  does not exist " %os.path.split(p)[0])
        else :
            print("no path found")

        return False

