################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
    any.cpp
    all.cpp
    m_arithmetic.cpp
    as_integer.cpp
    as_bits.cpp
    as_real.cpp
    as_signed.cpp
    as_unsigned.cpp
    cardinal_of.cpp
    downgrade.cpp
    floating.cpp
    from_bits.cpp
    is_result_of_supported.cpp
    is_scalar.cpp
    is_signed.cpp
    make_integer.cpp
    make_real.cpp
    scalar_of.cpp
    sign_of.cpp
    strip.cpp
    upgrade.cpp
    set.cpp
   )

ADD_CUSTOM_TARGET(sdk.meta.unit)
ADD_DEPENDENCIES(sdk.unit sdk.meta.unit)  

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(sdk.meta.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
