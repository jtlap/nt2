##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

FIND_PACKAGE(GSL QUIET)

SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_FOUND ${GSL_FOUND})
SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_INCLUDE_DIR ${GSL_INCLUDE_DIR})
SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_LIBRARY_DIR ${GSL_LINK_DIRECTORIES})
SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_LIBRARIES ${GSL_LIBRARIES})
SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_FLAGS ${CMAKE_GSL_CXX_FLAGS})
SET(NT2_EXTERN.GSL_SPECFUN_DEPENDENCIES_EXTRA operator)
