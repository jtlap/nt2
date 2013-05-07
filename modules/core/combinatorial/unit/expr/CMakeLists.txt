##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  combs.cpp
  factor.cpp
  is_prime.cpp
  perms.cpp
  permsn.cpp
  primes.cpp
# List of scalar test files for toolbox combinatorial
   )

nt2_module_add_tests(core.combinatorial.expr.unit ${SOURCES})
