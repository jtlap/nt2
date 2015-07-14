##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
   acos.cpp
   acosd.cpp
   acospi.cpp
   acot.cpp
   acotd.cpp
   acotpi.cpp
   acsc.cpp
   acscd.cpp
   asec.cpp
   asecd.cpp
   asin.cpp
   asind.cpp
   asinpi.cpp
   atan.cpp
   atan2.cpp
   atand.cpp
   atanpi.cpp
   cos.cpp
   cosd.cpp
   cosecant.cpp
   cosine.cpp
   cospi.cpp
   cot.cpp
   cotangent.cpp
   cotd.cpp
   cotpi.cpp
   csc.cpp
   cscd.cpp
   cscpi.cpp
   sec.cpp
   fast_cos.cpp
   fast_cosd.cpp
   fast_cospi.cpp
   fast_cot.cpp
   fast_cotd.cpp
   fast_cotpi.cpp
   fast_sin.cpp
   fast_sincos.cpp
   fast_sincosd.cpp
   fast_sincospi.cpp
   fast_sind.cpp
   fast_sinpi.cpp
   fast_tan.cpp
   fast_tand.cpp
   fast_tanpi.cpp
   indeg.cpp
   inrad.cpp
   proper_tanpi.cpp
   secant.cpp
   secd.cpp
   secpi.cpp
   sin.cpp
   sinc.cpp
   sincos.cpp
   sincpi.cpp
   sincosd.cpp
   sincospi.cpp
   sind.cpp
   sine.cpp
   sinecosine.cpp
   sinpi.cpp
   tan.cpp
   tand.cpp
   tangent.cpp
   tanpi.cpp
# List of scalar test files for toolbox trigonometric
   )

nt2_module_add_tests(core.trig_derivatives.scalar.unit ${SOURCES})
