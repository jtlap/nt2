#! /usr/bin/env python
# -*- coding: iso-8859-15  -*-
"""Init file for utilities
"""

__author__    = "Lapreste Jean-thierry (lapreste@univ-bpclermont.fr)"
__version__   = "$Revision: 1.0 $"
__date__      = "$Date: 2010 $"
__copyright__ = "Copyleft (c) 2010 Jean-thierry Lapreste"
__license__   = "Python"

import sys
import os
sys.path.insert(0,os.path.join(os.path.dirname(os.path.realpath(__file__)),'..'))

import files_utils
import display_utils
import re_list_utils
import iter_utils

sys.path.pop(0)
