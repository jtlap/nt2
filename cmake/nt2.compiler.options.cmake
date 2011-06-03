################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Fix CMAKE_BUILD_TYPE
################################################################################
INCLUDE(NT2Module)
nt2_setup_variant()

################################################################################
# Check for special options
################################################################################
INCLUDE(options/nt2.extra.warnings)
STRING(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_U)
SET(CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_U} "${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_U}} ${NT2_FLAGS}")
SET(CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_U} "${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE_U}} ${NT2_FLAGS}")

################################################################################
# Log current choice
################################################################################
MESSAGE( STATUS "[nt2] build type: ${CMAKE_BUILD_TYPE} (${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_U}})" )