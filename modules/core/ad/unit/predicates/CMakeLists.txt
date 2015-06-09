##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
# List of scalar test files for toolbox ad
   is_denormal.cpp
   is_equal_with_equal_nans.cpp
   is_eqz.cpp
   is_even.cpp
   is_finite.cpp
   is_flint.cpp
   is_gez.cpp
   is_gtz.cpp
   is_imag.cpp
   is_inf.cpp
   is_invalid.cpp
   is_lez.cpp
   is_ltz.cpp
   is_nan.cpp
   is_negative.cpp
   is_nez.cpp
   is_ngez.cpp
   is_ngtz.cpp
   is_nlez.cpp
   is_nltz.cpp
   is_not_denormal.cpp
   is_not_equal_with_equal_nans.cpp
   is_not_finite.cpp
   is_not_greater_equal.cpp
   is_not_greater.cpp
   is_not_imag.cpp
   is_not_infinite.cpp
   is_not_less_equal.cpp
   is_not_less.cpp
   is_not_nan.cpp
   is_not_real.cpp
   is_odd.cpp
   is_ord.cpp
   is_positive.cpp
   is_real.cpp
   is_unord.cpp
   )

nt2_module_add_tests(core.ad.predicates.unit ${SOURCES})
