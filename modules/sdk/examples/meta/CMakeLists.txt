################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(SOURCES
    has_key.cpp
    is_set.cpp
    join.cpp
    any.cpp
    enable_if_type.cpp
    strip.cpp
    make_real.cpp
    make_integer.cpp
    as_bits.cpp
    from_bits.cpp
    as_integer.cpp
    as_real.cpp
    as_signed.cpp
    as_unsigned.cpp
    sign_of.cpp
    is_signed.cpp
    downgrade.cpp
    upgrade.cpp
    is_fundamental.cpp
    is_unspecified.cpp
    )

ADD_CUSTOM_TARGET(sdk.meta.examples)
ADD_DEPENDENCIES(sdk.examples sdk.meta.examples)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(sdk.meta.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()

