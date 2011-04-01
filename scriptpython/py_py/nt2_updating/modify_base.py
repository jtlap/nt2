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


"""transitionnal doc conversion utlity
"""
__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import os
import sys
import shutil

sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..',"utils"))
from files_utils import write, exist, read
sys.path.pop(0)

class Modify_base(object) :
    @classmethod
    def duplicate(self, pin, pout,verbose=False) :
        if not exist(pout) :
            if verbose : print("duplicating \n  %s \nto \n  %s" %(pin,pout) )
            shutil.copy(pin,pout)
        elif verbose :
            print("file \n  %s \nis not duplicated as \n  %s \nalready exists" %(pin,pout) ) 
    
    @classmethod
    def restore(self,pin, pout,verbose=False) :
        if exist(pout) :
            if verbose : print("restoring \n  %s \nfrom \n  %s" %(pin,pout) )
            shutil.copy(pin,pout)
        elif verbose :
           print("file \n  %s \nis not restored as \n  %s \ndoes not exist" %(pout,pin) ) 
    
