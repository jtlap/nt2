##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  cart2pol.cpp
  cart2sph.cpp
  fast_sincos.cpp
  fast_sincosd.cpp
  fast_sincospi.cpp
  pol2cart.cpp
  sph2cart.cpp
  rem_pio2_cephes.cpp
  rem_pio2_straight.cpp
  rem_pio2_medium.cpp
  rem_pio2.cpp
  sincos.cpp
  sincosd.cpp
  sincospi.cpp
  sinecosine.cpp
# List of scalar test files for toolbox trigonometric
   )

nt2_module_add_tests(core.trigonometric.table.unit ${SOURCES})
