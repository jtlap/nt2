################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# fdlibm only works on 32-bit non-windows systems
IF(NOT CMAKE_SIZEOF_VOID_P EQUAL 4 OR WIN32)
  SET(NT2_EXTERN.FDLIBM_DEPENDENCIES_FOUND 0)
ENDIF()
SET(NT2_EXTERN.FDLIBM_DEPENDENCIES_EXTRA operator)

SET(NT2_EXTERN.FDLIBM_LIBRARIES nt2_fdlibm)
