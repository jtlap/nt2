################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(SOURCES
    arithmetic.cpp
    as_signed.cpp
    as_unsigned.cpp
    behave_as.cpp
    downgrade.cpp
    factory_of.cpp
    is_fundamental.cpp
    is_iterator.cpp
    is_result_of_supported.cpp
    is_scalar.cpp
    is_signed.cpp
    is_unspecified.cpp
    make_integer.cpp
    make_floating.cpp
    primitive_of.cpp
    sign_of.cpp
    strip.cpp
    upgrade.cpp
    )

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(sdk.meta.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()


