################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(NT2 COMPONENTS common polynomials)
SET(NT2_TRIGONOMETRIC_DEPENDENCIES_INCLUDE_DIR ${NT2_COMMON_INCLUDE_DIR} ${NT2_POLYNOMIALS_INCLUDE_DIR})
