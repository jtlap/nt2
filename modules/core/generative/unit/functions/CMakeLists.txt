##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  cic.cpp
  cif.cpp
  colon.cpp
  cols.cpp
  eye.cpp
  falses.cpp
  freqspace.cpp
  freqspace1.cpp
  freqspace2.cpp
  indices.cpp
  infs.cpp
  linspace.cpp
  logspace.cpp
  nans.cpp
  ones.cpp
  pispace.cpp
  rand.cpp
  rephorz.cpp
  repmat.cpp
  repnum.cpp
  repvert.cpp
  ric.cpp
  rif.cpp
  rows.cpp
  trues.cpp
  zeros.cpp
# List of simd test files for toolbox generative
   )

nt2_module_add_tests(core.generative.functions.unit ${SOURCES})
