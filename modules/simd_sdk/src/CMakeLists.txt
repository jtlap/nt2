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

include(nt2.preprocess)
nt2_preprocess(simd_sdk0x.preprocess ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/functor/functor.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/functor/details/dispatch.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/functor/meta/call.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/dsl/call.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/meta/arithmetic.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/meta/floating.hpp
                                     ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/meta/result_of.hpp
              )
              
nt2_preprocess(simd_sdk03.preprocess ${NT2_SIMD_SDK_ROOT}/include/boost/simd/sdk/functor/functor.hpp
               OPTIONS -DBOOST_SIMD_CREATE_PREPROCESSED_FILES_NO_0X
              )
              
add_custom_target(simd_sdk.preprocess DEPENDS simd_sdk0x.preprocess simd_sdk03.preprocess)
