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


"""utilities to add a line in a file
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
import re
from files_utils       import read, write, exist

class Add_str(object) :
    def __init__(self,path_to,verbose=False) :
        self.path_to = path_to
        self.verbose = verbose

    @classmethod
    def insert_after(cls,token, txt, line2add) :
        """ insertion of a line after a line
        containing a token in a list of lines
        """
        pattern = re.compile(line2add)
        def find_index(p) :
            for i,l in enumerate(txt) :
                if p.match(l) : return i+1
            return 0
        if find_index(pattern) :
            return (False,txt)
        else :
            #### match for token
            pattern = re.compile(token)
            i = find_index(pattern)
            if i != 0 : txt.insert(i,line2add)
            return (True,txt)

    def update_file(self,token,txt) :
        txt_orig = read(self.path_to)
        done, new_txt = self.insert_after(token,txt_orig,txt)
        if not done :
            print("Warning : line\n  %s\nis already in %s file"% (txt,self.path_to))
        else :
            if exist(self.path_to) :
                if self.verbose : print("file\n  %s\nwill be updated"%self.path_to)
                write(self.path_to,new_txt,False)
                if self.verbose : print("file\n  %s\nis now updated"%self.path_to)
            else :
                if self.verbose : print("file\n  %s\n does not exist"%self.path_to)

if __name__ == "__main__" :
    rep='/home/jt/DevC++/pipo/nt2/modules/fdlibm/include/nt2/toolbox/fdlibm/function/scalar/'

    files = [f for f in os.listdir(rep) if re.match(r'.*\.hpp$', f)]
    for f in files :
        print(f)
        al = Add_str('/home/jt/DevC++/pipo/nt2/modules/fdlibm/include/nt2/toolbox/fdlibm/function/scalar/'+f)
        al.update_file("#define","#include <nt2/sdk/meta/upgrade.hpp>")


