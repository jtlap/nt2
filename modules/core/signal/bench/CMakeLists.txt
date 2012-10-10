##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

nt2_module_use_modules(unit core.utility)

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework Accelerate")
endif()

SET( SOURCES
    static_fft.cpp
# List of simd test files for toolbox signal
   )

nt2_module_add_tests(core.signal.simd.bench ${SOURCES})
