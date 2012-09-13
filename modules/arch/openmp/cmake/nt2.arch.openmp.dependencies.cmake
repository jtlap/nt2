################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(OpenMP QUIET)

SET(NT2_OPENMP_DEPENDENCIES_FOUND ${OPENMP_FOUND})
SET(NT2_OPENMP_COMPILE_FLAGS ${OpenMP_C_FLAGS})
SET(NT2_OPENMP_LINK_FLAGS ${OpenMP_C_FLAGS})
SET(NT2_OPENMP_DEPENDENCIES_EXTRA core.utility)
