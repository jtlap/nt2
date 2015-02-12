##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  shuffle.cpp
  shuffle2.cpp
  shuffle4.cpp
  shuffle8.cpp
  shuffle16.cpp
  all_reduce.cpp
  broadcast.cpp
  combine.cpp
  cummin.cpp
  cummax.cpp
  cumsum.cpp
  cumprod.cpp
  enumerate.cpp
  group.cpp
  groups.cpp
  lookup.cpp
  slice.cpp
  sort.cpp
  splatted_maximum.cpp
  splatted_minimum.cpp
  splatted_prod.cpp
  splatted_sum.cpp
  split.cpp
  split_high.cpp
  split_low.cpp
  reverse.cpp
  deinterleave_first.cpp
  deinterleave_second.cpp
  interleave_first.cpp
  interleave_even.cpp
  interleave_odd.cpp
  interleave_second.cpp
  repeat_lower_half.cpp
  repeat_upper_half.cpp
  split_multiplies.cpp
  #shuffle_meta.cpp
# List of simd test files for toolbox swar
   )

nt2_module_add_tests(boost.simd.base.swar.simd.unit ${SOURCES})
