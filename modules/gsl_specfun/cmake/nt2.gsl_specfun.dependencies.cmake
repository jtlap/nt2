##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET(GSL_FIND_QUIETLY 1)

FIND_PACKAGE(NT2 COMPONENTS sdk)
FIND_PACKAGE(GSL)
IF(NOT NT2_FOUND OR NOT GSL_FOUND)
  SET(NT2_GSL_SPECFUN_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_GSL_SPECFUN_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_GSL_SPECFUN_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR} ${GSL_INCLUDE_DIR})
SET(NT2_GSL_SPECFUN_DEPENDENCIES_LIBRARY_DIR ${NT2_LIBRARY_DIR} ${GSL_LINK_DIRECTORIES})
SET(NT2_GSL_SPECFUN_DEPENDENCIES_LIBRARIES ${NT2_LIBRARIES} ${GSL_LIBRARIES})
SET(NT2_GSL_SPECFUN_DEPENDENCIES_FLAGS "${NT2_FLAGS} ${CMAKE_GSL_CXX_FLAGS}")
