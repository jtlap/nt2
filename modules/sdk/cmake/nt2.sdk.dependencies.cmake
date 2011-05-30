################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(NT2 COMPONENTS config)

IF(NOT NT2_FOUND)
  SET(NT2_SDK_DEPENDENCIES_FOUND 0)
  RETURN()
ENDIF()

SET(NT2_SDK_DEPENDENCIES_FOUND 1)
SET(NT2_SDK_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR})
SET(NT2_SDK_DEPENDENCIES_LIBRARY_DIR ${NT2_CONFIG_DEPENDENCIES_LIBRARY_DIR} ${NT2_LIBRARIES})
SET(NT2_SDK_DEPENDENCIES_FLAGS ${NT2_FLAGS})
SET(NT2_SDK_FLAGS ${NT2_CONFIG_FLAGS})
SET(NT2_SDK_LIBRARIES nt2)
