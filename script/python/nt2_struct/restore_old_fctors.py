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


"""Utilities to get toolboxes informations
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010    $"
__copyright__ = """ Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
                    Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI"""
__license__   = "Boost Software License, Version 1.0"

import sys
import os
import re
from files_utils            import read, exist
from nt2_toolbox_infos      import Toolbox_infos
from nt2_fundamentals       import Nt2_base_infos
from nt2_tb_functors_infos  import Fctor_infos
from display_utils          import show
from mk_new_functor         import Mk_fctor       
tb_targets =[
    "gsl_specfun",
    "swar",
    "fdlibm",
    "boost_math",
    "predicates",
    "libc",
    "ieee",
    "bitwise",
    "reduction",
    "polynomials",
    "trigonometric",
    "fuzzy",
    "hyperbolic",
    "bessel",
    "exponential",
    "euler",
    "elliptic",
    "ast",
    "combinatorial",
    "cephes",
    "standard",
    "arithmetic",
    "crlibm"
]



for tb in tb_targets :
    tbi = Toolbox_infos(tb)
    isas = tbi.nbi.get_implanted_archis()
    if tbi.get_tb_style() =='sys' :
        print tb
        for isa in isas :
            if isa != 'scalar' :
                print isa
                for fct in tbi.get_fctors_list() :
                    for sub in tbi.nbi.get_archis().submodes(isa) :
                        fi = Fctor_infos(tb,fct,isa,sub)
                        print "%s\n" % os.path.join(isa,sub,fct+'.hpp')
                        mf = Mk_fctor(fi)
                        mf.revert_to_old_fctor()
                        print "="*50
                
 
