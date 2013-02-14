################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.simd)

MESSAGE( STATUS "[boost.simd.sdk] target system: ${NT2_OS} (${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION})" )
MESSAGE( STATUS "[boost.simd.sdk] target processor: ${NT2_ARCH} (${CMAKE_SYSTEM_PROCESSOR})" )
MESSAGE( STATUS "[boost.simd.sdk] compiler: ${NT2_COMPILER} (${CMAKE_CXX_COMPILER_ID})" )

# Disable useless qualifier flag because of const-return trick used by Proto
set(FLAGS ${NT2_SIMD_FLAGS})
if(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  if(UNIX)
    set(FLAGS "${FLAGS} -wd411 -wd2536 -Dsimd=_Simd")
  else()
    set(FLAGS "${FLAGS} /wd411 /wd2536 -Dsimd=_Simd")
  endif()
endif()

SET(NT2_BOOST.SIMD.SDK_COMPILE_FLAGS ${FLAGS})
SET(NT2_BOOST.SIMD.SDK_DEPENDENCIES_EXTRA boost.dispatch boost.simd.config)
