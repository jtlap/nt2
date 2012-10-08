##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  knuth_equal.cpp
  fuzzy_less_or_equal.cpp
  fuzzy_greater_or_equal.cpp
  fuzzy_equal.cpp
  fuzzy_definitely_not_equal.cpp
  fuzzy_definitely_less.cpp
  fuzzy_definitely_greater.cpp
  definitely_not_equal.cpp
  definitely_less.cpp
  definitely_greater.cpp
  almost_less_or_equal.cpp
  almost_greater_or_equal.cpp
  almost_equal.cpp
# List of scalar test files for toolbox fuzzy
   )

nt2_module_add_tests(core.fuzzy.scalar.bench ${SOURCES})
