################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(SOURCES
    unary_plus.cpp
    complement.cpp
    logical_not.cpp
    neg.cpp
    plus.cpp
    minus.cpp
    multiplies.cpp
    divides.cpp
    bitwise_and.cpp
    bitwise_or.cpp
    bitwise_xor.cpp
    logical_and.cpp
    logical_or.cpp
    comma.cpp
    if_else.cpp
    modulo.cpp
    shift_left.cpp
    shift_right.cpp
    is_equal.cpp
    is_not_equal.cpp
    is_less.cpp
    is_greater.cpp
    is_less_equal.cpp
    is_greater_equal.cpp
    )

ADD_CUSTOM_TARGET(sdk.functor.unit)
ADD_DEPENDENCIES(sdk.unit sdk.functor.unit)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(sdk.functor.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()

