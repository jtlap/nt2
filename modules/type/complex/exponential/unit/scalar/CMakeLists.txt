##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set( SOURCES
   exp.cpp
   exp10.cpp
   exp2.cpp
   expm1.cpp
   log.cpp
   log10.cpp
   log2.cpp
   log1p.cpp
   sqrt1pm1.cpp
   pow2.cpp
   )

nt2_module_add_tests(type.complex.exponential.scalar.unit ${SOURCES})
