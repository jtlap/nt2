
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  unary_plus.cpp
  unary_minus.cpp
  store.cpp
  splat.cpp
  shift_right.cpp
  shift_left.cpp
  plus.cpp
  multiplies.cpp
  modulo.cpp
  minus.cpp
  map.cpp
  make.cpp
  logical_or.cpp
  logical_not.cpp
  logical_and.cpp
  load.cpp
  if_else.cpp
  divides.cpp
  complement.cpp
  is_not_equal.cpp
  is_less_equal.cpp
  is_less.cpp
  is_greater_equal.cpp
  is_greater.cpp
  is_equal.cpp
  comma.cpp
  bitwise_xor.cpp
  bitwise_or.cpp
  bitwise_and.cpp
# List of scalar test files for toolbox operator
   )

nt2_module_add_tests(core.operator.scalar.cover ${SOURCES})

