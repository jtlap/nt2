################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(Boost_ADDITIONAL_VERSIONS "1.48")
FIND_PACKAGE( Boost 1.48.0 QUIET )

SET(NT2_SDK.ERROR_DEPENDENCIES_FOUND ${Boost_FOUND})
SET(NT2_SDK.ERROR_DEPENDENCIES_INCLUDE_DIR ${Boost_INCLUDE_DIRS})
SET(NT2_SDK.ERROR_DEPENDENCIES_LIBRARY_DIR ${Boost_LIBRARY_DIRS})
