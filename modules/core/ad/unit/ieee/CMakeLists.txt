##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES

# List of scalar test files for toolbox ad
   copysign.cpp
   frac.cpp
   ldexp.cpp
   maxmag.cpp
   maxnum.cpp
   maxnummag.cpp
   minmag.cpp
   minnum.cpp
   minnummag.cpp
   negate.cpp
   negatenz.cpp
   sign.cpp
   signnz.cpp
   )

nt2_module_add_tests(core.ad.ieee.unit ${SOURCES})
