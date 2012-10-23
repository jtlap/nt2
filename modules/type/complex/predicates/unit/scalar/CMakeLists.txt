##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set( SOURCES
     is_eqz.cpp
     is_finite.cpp
     is_inf.cpp
     is_invalid.cpp
     is_nan.cpp
     is_nez.cpp
     is_not_finite.cpp
     is_not_infinite.cpp
     is_not_nan.cpp
     is_real.cpp
     is_imag.cpp
   )

nt2_module_add_tests(type.complex.predicates.scalar.unit ${SOURCES})
