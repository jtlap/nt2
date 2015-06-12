##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
   d_acos.cpp
   d_acosd.cpp
   d_acospi.cpp
   d_acotd.cpp
   d_acot.cpp
   d_acscd.cpp
   d_acsc.cpp
   d_asecd.cpp
   d_asec.cpp
   d_asind.cpp
   d_asin.cpp
   d_asinpi.cpp
   d_atand.cpp
   d_atan.cpp
   d_atanpi.cpp
   d_cosd.cpp
   d_cosecant.cpp
   d_cos.cpp
   d_cosine.cpp
   d_cospi.cpp
   d_cotangent.cpp
   d_cotd.cpp
   d_cot.cpp
   d_cotpi.cpp
   d_cscd.cpp
   d_csc.cpp
   d_cscpi.cpp
   d_fast_cosd.cpp
   d_fast_cos.cpp
   d_fast_cospi.cpp
   d_fast_cotd.cpp
   d_fast_cot.cpp
   d_fast_cotpi.cpp
   d_fast_sincosd.cpp
   d_fast_sincos.cpp
   d_fast_sincospi.cpp
   d_fast_sind.cpp
   d_fast_sin.cpp
   d_fast_sinpi.cpp
   d_fast_tand.cpp
   d_fast_tan.cpp
   d_fast_tanpi.cpp
   d_proper_tanpi.cpp
   d_secant.cpp
   d_secd.cpp
   d_sec.cpp
   d_secpi.cpp
   d_sinc.cpp
   d_sincosd.cpp
   d_sincos.cpp
   d_sincospi.cpp
   d_sincpi.cpp
   d_sind.cpp
   d_sinecosine.cpp
   d_sine.cpp
   d_sin.cpp
   d_sinpi.cpp
   d_tand.cpp
   d_tangent.cpp
   d_tan.cpp
   d_tanpi.cpp
# List of scalar test files for toolbox trigonometric
   )

nt2_module_add_tests(core.trig_derivatives.scalar.unit ${SOURCES})
