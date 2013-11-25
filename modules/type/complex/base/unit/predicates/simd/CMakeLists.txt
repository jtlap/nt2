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
     is_lez.cpp
     is_gez.cpp
     is_gtz.cpp
     is_ltz.cpp
     is_nlez.cpp
     is_ngez.cpp
     is_ngtz.cpp
     is_nltz.cpp
     is_equal_with_equal_nans.cpp
     is_not_equal_with_equal_nans.cpp
     is_not_imag.cpp
     is_not_real.cpp
     is_equal.cpp
     is_not_equal.cpp
   )

nt2_module_add_tests(type.complex.base.predicates.simd.unit ${SOURCES})
