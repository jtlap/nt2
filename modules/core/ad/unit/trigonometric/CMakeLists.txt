##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
   acos.cpp
   acosd.cpp
   acospi.cpp
   acotd.cpp
   acot.cpp
   acscd.cpp
   acsc.cpp
   asecd.cpp
   asec.cpp
   asind.cpp
   asin.cpp
   asinpi.cpp
   atand.cpp
   atan.cpp
   atanpi.cpp
   cosd.cpp
   cosecant.cpp
   cos.cpp
   cosine.cpp
   cospi.cpp
   cotangent.cpp
   cotd.cpp
   cot.cpp
   cotpi.cpp
   cscd.cpp
   csc.cpp
   cscpi.cpp
   fast_cosd.cpp
   fast_cos.cpp
   fast_cospi.cpp
   fast_cotd.cpp
   fast_cot.cpp
   fast_cotpi.cpp
   fast_sincosd.cpp
   fast_sincos.cpp
   fast_sincospi.cpp
   fast_sind.cpp
   fast_sin.cpp
   fast_sinpi.cpp
   fast_tand.cpp
   fast_tan.cpp
   fast_tanpi.cpp
   proper_tanpi.cpp
   secant.cpp
   secd.cpp
   sec.cpp
   secpi.cpp
   sinc.cpp
   sincosd.cpp
   sincos.cpp
   sincospi.cpp
   sincpi.cpp
   sind.cpp
   sinecosine.cpp
   sine.cpp
   sin.cpp
   sinpi.cpp
   tand.cpp
   tangent.cpp
   tan.cpp
   tanpi.cpp
# List of scalar test files for toolbox ad
   )

nt2_module_add_tests(core.ad.trigonometric.unit ${SOURCES})






