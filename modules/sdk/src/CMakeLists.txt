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

file( GLOB_RECURSE source_sdk_files
      ${NT2_SDK_ROOT}/src/*
    )
SET(SOURCES ${source_sdk_files} ${NT2_CONFIG_ROOT}/src/version.cpp)
nt2_module_add_library(nt2 ${SOURCES})

include(nt2.preprocess)
nt2_preprocess(sdk.preprocess ${NT2_SDK_ROOT}/include/nt2/sdk/functor/functor.hpp
                              ${NT2_SDK_ROOT}/include/nt2/sdk/functor/meta/call.hpp
                              ${NT2_SDK_ROOT}/include/nt2/sdk/dsl/call.hpp
                              ${NT2_SDK_ROOT}/include/nt2/sdk/meta/arithmetic.hpp
                              ${NT2_SDK_ROOT}/include/nt2/sdk/meta/floating.hpp
              )
