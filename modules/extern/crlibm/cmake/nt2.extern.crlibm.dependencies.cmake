################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_LIBRARY(CRLIBM_LIBRARY crlibm)
IF(CRLIBM_LIBRARY MATCHES "NOTFOUND$")
  SET(NT2_EXTERN.CRLIBM_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_EXTERN.CRLIBM_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_EXTERN.CRLIBM_DEPENDENCIES_LIBRARIES ${CRLIBM_LIBRARY})
SET(NT2_EXTERN.CRLIBM_DEPENDENCIES_EXTRA core.operator)
