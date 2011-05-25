################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(sdk)

################################################################################
# Generate bootstrap.hpp
################################################################################
CONFIGURE_FILE( ${NT2_SDK_ROOT}/src/bootstrap.hpp.cmake
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )
              
nt2_module_configure_simd( nt2/sdk/simd/details/impl --no-simd-dir --no-default-baseline
                                                     -Bcommon -Bsse/sse2
                         )

file( GLOB_RECURSE source_files
      ${NT2_SDK_ROOT}/src/*
    )
    
nt2_module_add_library(nt2 ${source_files})

macro(preprocess_file target)
  find_file(WAVE_EXECUTABLE wave $ENV{BOOST_ROOT}/dist/bin)
  get_directory_property(INCLUDES INCLUDE_DIRECTORIES)
  
  if(NT2_PROCESSOR STREQUAL x86)
    set(INCLUDE_ARCH i686)
  else()
    set(INCLUDE_ARCH ${NT2_PROCESSOR})
  endif()
  set(INCLUDE_DIRECTORIES -S/usr/lib/gcc/${INCLUDE_ARCH}-linux-gnu/4.5/include
                          -S/usr/include/c++/4.5
                          -S/usr/include/c++/4.5/${INCLUDE_ARCH}-linux-gnu
                          -S/usr/include
     )

  foreach(INCLUDE ${INCLUDES})
    list(APPEND INCLUDE_DIRECTORIES "-S${INCLUDE}")
  endforeach()
  set(prev 0)
  foreach(src ${ARGN})
    math(EXPR n "${prev} + 1")
    add_custom_target(${target}.${n}
                      COMMAND echo "wave ${src}" && ${WAVE_EXECUTABLE} -DNT2_DONT_USE_PREPROCESSED_FILES -DNT2_CREATE_PREPROCESSED_FILES --c++0x --timer ${INCLUDE_DIRECTORIES} -o - ${src}
                      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/include
                     )
    if(prev)
      add_dependencies(${target}.${n} ${target}.${prev}) # we force sequential execution
    endif()
    set(prev ${n})
  endforeach()
  add_custom_target(${target})
  add_dependencies(${target} ${target}.${prev})
endmacro()

preprocess_file(sdk.preprocess ${NT2_SDK_ROOT}/include/nt2/sdk/functor/functor.hpp
                               ${NT2_SDK_ROOT}/include/nt2/sdk/functor/meta/call.hpp
               )
