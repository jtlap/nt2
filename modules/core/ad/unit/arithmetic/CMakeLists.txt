##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
   sqr.cpp
   abs.cpp
   arg.cpp
   average.cpp
   conj.cpp
   dec.cpp
   dist.cpp
   fma.cpp
   fms.cpp
   fnma.cpp
   fnms.cpp
   hypot.cpp
   inc.cpp
   max.cpp
   min.cpp
#   minmod.cpp  waiting for if_else_zero
   oneminus.cpp
   oneplus.cpp
   rec.cpp
   sqr_abs.cpp
   sqrt.cpp
# List of scalar test files for toolbox ad
   )

nt2_module_add_tests(core.ad.arithmetic.unit ${SOURCES})
