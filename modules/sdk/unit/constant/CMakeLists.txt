################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(SOURCES
    digits.cpp
    eps.cpp
    infinites.cpp
    properties.cpp
    real.cpp
    splat.cpp
    )

ADD_CUSTOM_TARGET(sdk.constant.unit)
ADD_DEPENDENCIES(sdk.unit sdk.constant.unit)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(sdk.constant.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
