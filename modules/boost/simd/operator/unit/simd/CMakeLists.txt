################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  unary_plus.cpp
  store.cpp
  map.cpp
  make.cpp
  load.cpp
  unaligned_load.cpp
  unaligned_store.cpp
  if_else.cpp
  is_less_equal.cpp
  is_less.cpp
  is_greater_equal.cpp
  is_greater.cpp
  access.cpp
  bitwise_and.cpp
  bitwise_or.cpp
  bitwise_xor.cpp
  comma.cpp
  is_equal.cpp
  is_not_equal.cpp
  complement.cpp
  divides.cpp
  logical_and.cpp
  logical_not.cpp
  logical_or.cpp
  minus.cpp
  modulo.cpp
  multiplies.cpp
  unary_minus.cpp
  plus.cpp
  shift_left.cpp
  shift_right.cpp
  splat.cpp
  stream.cpp
  )

nt2_module_add_tests(boost.simd.operator.simd.unit ${SOURCES})

