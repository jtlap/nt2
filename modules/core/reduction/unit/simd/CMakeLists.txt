##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  none.cpp
  at_i.cpp
  hmsb.cpp
  sum.cpp
  second.cpp
  prod.cpp
  posmin.cpp
  posmax.cpp
  nbtrue.cpp
  minimum.cpp
  maximum.cpp
  first.cpp
  dot.cpp
  all.cpp
  any.cpp
  compare_equal.cpp
  compare_not_equal.cpp
  compare_less.cpp
  compare_less_equal.cpp
  compare_greater.cpp
  compare_greater_equal.cpp
# List of simd test files for toolbox reduction
   )

nt2_module_add_tests(core.reduction.simd.unit ${SOURCES})
