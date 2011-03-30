################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(NT2 COMPONENTS sdk)
FIND_LIBRARY(CRLIBM_LIBRARY crlibm)

IF(NOT NT2_FOUND OR CRLIBM_LIBRARY MATCHES "NOTFOUND")
  SET(NT2_CRLIBM_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_CRLIBM_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_CRLIBM_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR})
SET(NT2_CRLIBM_DEPENDENCIES_LIBRARIES ${NT2_LIBRARIES} ${CRLIBM_LIBRARY})
SET(NT2_CRLIBM_DEPENDENCIES_FLAGS ${NT2_FLAGS})
