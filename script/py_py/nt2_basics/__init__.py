#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Init file for nt2 toolbox manipulation 
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"
import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..'))


import nt2_fundamentals
import nt2_archis
import nt2_toolbox_infos
import nt2_tb_functors

sys.path.pop(0)
