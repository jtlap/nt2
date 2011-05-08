################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(SOURCES
    assertion_failed.cpp
    timestamp.cpp
    ignore_unused.cpp
    bitwise_cast.cpp
    
# preprocessor examples
    pp_enum_value.cpp
    pp_include.cpp
    pp_index.cpp
    pp_strip.cpp
    
# meta examples
    decltype.cpp
    type_id.cpp
    display_type.cpp
    )

ADD_CUSTOM_TARGET(sdk.details.examples)
ADD_DEPENDENCIES(sdk.examples sdk.details.examples)

################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(sdk.details.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()


