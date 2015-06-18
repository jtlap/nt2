##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES

# List of scalar test files for toolbox ad
   acosh.cpp
   acoth.cpp
   acsch.cpp
   asech.cpp
   asinh.cpp
   atanh.cpp
   cosh.cpp
   coth.cpp
   csch.cpp
   sech.cpp
   sinhc.cpp
   sinhcosh.cpp
   sinh.cpp
   tanh.cpp
   )

nt2_module_add_tests(core.ad.hyperbolic.unit ${SOURCES})






