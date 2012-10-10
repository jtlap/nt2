##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set(SOURCES test.cpp)

if(APPLE)
  foreach(build_type NT2Test NT2TestDebug)
    string(TOUPPER ${build_type} build_type_U)
    set(CMAKE_EXE_LINKER_FLAGS_${build_type_U} "${CMAKE_EXE_LINKER_FLAGS_${build_type_U}} -framework Accelerate")
  endforeach()
endif()

nt2_module_add_tests(core.signal.unit ${SOURCES})
