################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(Matlab)

SET(NT2_MATLAB_DEPENDENCIES_FOUND ${MATLAB_FOUND})
SET(NT2_MATLAB_DEPENDENCIES_INCLUDE_DIR ${MATLAB_INCLUDE_DIR})
SET(NT2_MATLAB_DEPENDENCIES_LIBRARIES ${MATLAB_MX_LIBRARY} ${MATLAB_MCR_LIBRARY})
SET(NT2_MATLAB_DEPENDENCIES_EXTRA sdk)

SET(NT2_MATLAB_LIBRARIES nt2_mw)
