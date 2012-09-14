##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  genmask.cpp
  twopower.cpp
  shri.cpp
  shrai.cpp
  shli.cpp
  rshr.cpp
  rshl.cpp
  rror.cpp
  rrol.cpp
  ror.cpp
  rol.cpp
  reversebits.cpp
  popcnt.cpp
  lo.cpp
  hi.cpp
  firstbitunset.cpp
  firstbitset.cpp
  ffs.cpp
  bitwise_select.cpp
  bitwise_notand.cpp
  bitwise_andnot.cpp
  bitwise_ornot.cpp
  bitwise_notor.cpp
  bits.cpp
# List of simd test files for toolbox bitwise
   )

nt2_module_add_tests(core.bitwise.simd.unit ${SOURCES})
