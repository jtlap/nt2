################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.boost)
include(nt2.simd)

################################################################################
# Generate bootstrap.hpp
################################################################################
FIND_FILE(NT2_SDK_BOOTSTRAP_FILE bootstrap.hpp.cmake ${CMAKE_MODULE_PATH})
CONFIGURE_FILE( ${NT2_SDK_BOOTSTRAP_FILE}
                ${PROJECT_BINARY_DIR}/include/nt2/sdk/config/bootstrap.hpp
              )

FIND_PACKAGE(NT2 COMPONENTS extension)

IF(NOT Boost_FOUND OR NOT NT2_FOUND)
  SET(NT2_SDK_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_SDK_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_SDK_DEPENDENCIES_INCLUDE_DIR ${Boost_INCLUDE_DIRS} ${NT2_INCLUDE_DIR})
SET(NT2_SDK_DEPENDENCIES_LIBRARY_DIR ${Boost_LIBRARY_DIRS})
SET(NT2_SDK_DEPENDENCIES_FLAGS ${NT2_FLAGS})
SET(NT2_SDK_FLAGS ${NT2_CXX_SIMD_FLAGS})
SET(NT2_SDK_LIBRARIES nt2)
