################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    as_integer.cpp
    as_real.cpp
    as_signed.cpp
    as_unsigned.cpp
    cardinal_of.cpp
    category_of.cpp
    downgrade.cpp
    is_signed.cpp
    is_simd_specific.cpp
    make_integer.cpp
    make_real.cpp
#    native.cpp
    native_cast.cpp
#    pack.cpp
    scalar_of.cpp
    sign_of.cpp
    upgrade.cpp
   )

ADD_CUSTOM_TARGET(sdk.simd.unit)
ADD_DEPENDENCIES(sdk.unit sdk.simd.unit)


################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(sdk.simd.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()

