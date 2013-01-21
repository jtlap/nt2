
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  split.cpp
  splatted_sum.cpp
  splatted_second.cpp
  splatted_prod.cpp
  splatted_minimum.cpp
  splatted_maximum.cpp
  splatted_first.cpp
#  sort.cpp
  put_first.cpp
  lookup.cpp
  group.cpp
  cumsum.cpp
  comparator.cpp
# List of simd test files for toolbox swar
   )

nt2_module_add_tests(core.swar.simd.cover ${SOURCES})

