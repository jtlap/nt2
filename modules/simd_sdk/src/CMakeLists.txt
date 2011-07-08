################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(simd_sdk)

file( GLOB_RECURSE source_simd_sdk_files
      ${NT2_SIMD_SDK_ROOT}/src/*
    )
SET(SOURCES ${source_simd_sdk_files} ${NT2_SIMD_CONFIG_ROOT}/src/version.cpp)
nt2_module_add_library(boost_simd ${SOURCES})
