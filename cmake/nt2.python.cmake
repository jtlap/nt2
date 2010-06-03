################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Should we build Python bindings
################################################################################
include(FindPythonInterp)
include(FindPythonLibs)
IF(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
SET(NT2_HAS_PYTHON_SUPPORT 1)
ENDIF(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)


