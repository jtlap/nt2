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
  foreach(build_type NT2Test NT2TestDebug)
    string(TOUPPER ${build_type} build_type_U)
    set(CMAKE_EXE_LINKER_FLAGS_${build_type_U} "${CMAKE_EXE_LINKER_FLAGS_${build_type_U}} -framework Accelerate")
  endif()
endif()

SET( SOURCES
    static_fft.cpp
# List of simd test files for toolbox signal
   )

nt2_module_add_tests(core.signal.simd.bench ${SOURCES})
