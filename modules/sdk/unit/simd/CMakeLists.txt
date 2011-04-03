################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    access.cpp
    as_integer.cpp
    as_real.cpp
    as_signed.cpp
    as_unsigned.cpp
    bitwise_and.cpp
    bitwise_or.cpp
    bitwise_xor.cpp
    cardinal_of.cpp
    category_of.cpp
    comma.cpp
    compare_equal.cpp
    compare_not_equal.cpp
    complement.cpp
    divides.cpp
    downgrade.cpp
    is_equal.cpp
    is_greater.cpp
    is_greater_equal.cpp
    is_less.cpp
    is_less_equal.cpp
    is_not_equal.cpp
    is_signed.cpp
    is_simd_specific.cpp
    logical_and.cpp
    logical_not.cpp
    logical_or.cpp
    make_integer.cpp
    make_real.cpp
    minus.cpp
    modulo.cpp
    multiplies.cpp
#    native.cpp
    native_cast.cpp
    neg.cpp
#    pack.cpp
    plus.cpp
    scalar_of.cpp
    sign_of.cpp
    shift_left.cpp
    shift_right.cpp
    upgrade.cpp
    splat.cpp
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

