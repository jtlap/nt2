##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  cbrt.cpp
  exp.cpp
  exp2.cpp
  exp10.cpp
  expm1.cpp
  exprecneg.cpp
  exprecnegc.cpp
  expx2.cpp
  log.cpp
  log2.cpp
  log10.cpp
  log1p.cpp
  logspace_add.cpp
  logspace_sub.cpp
  nthroot.cpp
  pow.cpp
  pow_abs.cpp
  reallog.cpp
  realpow.cpp
  realsqrt.cpp
  sqrt1pm1.cpp
# List of scalar test files for toolbox exp_derivatives
 )

nt2_module_add_tests(core.exp_derivatives.scalar.unit ${SOURCES})
