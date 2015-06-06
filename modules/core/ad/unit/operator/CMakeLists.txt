##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
   divides.cpp
   if_else.cpp
   is_equal.cpp
   is_greater.cpp
   is_greater_equal.cpp
   is_less.cpp
   is_less_equal.cpp
   is_not_equal.cpp
   unary_minus.cpp
   unary_plus.cpp
   minus.cpp
   multiplies.cpp
   plus.cpp

# List of scalar test files for toolbox ad
   )

nt2_module_add_tests(core.ad.operator.unit ${SOURCES})
