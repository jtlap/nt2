##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES

# List of scalar test files for toolbox ad
   cbrt.cpp
   exp10.cpp
   exp2.cpp
   exp.cpp
   expm1.cpp
   exprecnegc.cpp
   exprecneg.cpp
   expx2.cpp
   log10.cpp
   log1p.cpp
   log2.cpp
   log.cpp
   logspace_add.cpp
   logspace_sub.cpp
   nthroot.cpp
#   pow2.cpp
   pow_abs.cpp
   pow.cpp
   reallog.cpp
   realpow.cpp
   realsqrt.cpp
   sqrt1pm1.cpp
   )

nt2_module_add_tests(core.ad.exponential.unit ${SOURCES})






