##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  d_cbrt.cpp
  d_exp10.cpp
  d_exp2.cpp
  d_exp.cpp
  d_expm1.cpp
  d_exprecnegc.cpp
  d_exprecneg.cpp
  d_expx2.cpp
  d_log10.cpp
  d_log1p.cpp
  d_log2.cpp
  d_log.cpp
  d1_logspace_add.cpp
  d2_logspace_add.cpp
  d1_logspace_sub.cpp
  d2_logspace_sub.cpp
  d_nthroot.cpp
  d1_pow_abs.cpp
  d2_pow_abs.cpp
  d1_pow.cpp
  d2_pow.cpp
  d_reallog.cpp
  d_realsqrt.cpp
  d_sqrt1pm1.cpp
# List of scalar test files for toolbox exp_derivatives
 )

nt2_module_add_tests(core.exp_derivatives.scalar.unit ${SOURCES})
