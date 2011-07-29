################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    all.cpp
    any.cpp
    cardinal_of.cpp
    is_result_of_supported.cpp
   )

ADD_CUSTOM_TARGET(boost.simd.sdk.meta.unit)
ADD_DEPENDENCIES(boost.simd.sdk.unit boost.simd.sdk.meta.unit)  

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(boost.simd.sdk.meta.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
