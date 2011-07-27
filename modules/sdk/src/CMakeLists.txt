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

set(SOURCES
    details/timestamp.cpp
    error/assert_exception.cpp
    error/exception.cpp
    memory/allocate.cpp
    memory/deallocate.cpp
    memory/reallocate.cpp
    timing/now.cpp
    timing/timers.cpp
    config/version.cpp
   )
nt2_module_add_library(nt2 ${SOURCES})

include(nt2.preprocess)
nt2_preprocess(sdk0x.preprocess ${NT2_SDK_ROOT}/include/nt2/sdk/functor/functor.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/functor/details/dispatch.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/functor/meta/call.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/dsl/call.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/meta/arithmetic.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/meta/floating.hpp
                                ${NT2_SDK_ROOT}/include/nt2/sdk/meta/result_of.hpp
              )
              
nt2_preprocess(sdk03.preprocess ${NT2_SDK_ROOT}/include/nt2/sdk/functor/functor.hpp
               OPTIONS -DNT2_CREATE_PREPROCESSED_FILES_NO_0X
              )

if(NT2_PREPROCESS_ENABLED)              
  add_custom_target(sdk.preprocess)
  add_dependencies(sdk.preprocess sdk0x.preprocess sdk03.preprocess)
endif()
