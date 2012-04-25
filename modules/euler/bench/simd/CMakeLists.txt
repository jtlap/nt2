##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  erf.cpp
  erfc.cpp
  fast_gamma.cpp
  spence.cpp
  stirling.cpp
  dawson.cpp
  digamma.cpp
  signgam.cpp
  gammaln.cpp
  gamma.cpp
  beta.cpp
  expni.cpp
# List of simd test files for toolbox euler
   )

nt2_module_add_tests(euler.simd.bench ${SOURCES})
