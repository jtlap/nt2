##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  d_acosh.cpp
  d_acoth.cpp
  d_acsch.cpp
  d_asech.cpp
  d_asinh.cpp
  d_atanh.cpp
  d_cosh.cpp
  d_coth.cpp
  d_csch.cpp
  d_sech.cpp
  d_sinhc.cpp
  d_sinhcosh.cpp
  d_sinh.cpp
  d_tanh.cpp
# List of scalar test files for toolbox exp_derivatives
 )

nt2_module_add_tests(core.hyper_derivatives.scalar.unit ${SOURCES})
