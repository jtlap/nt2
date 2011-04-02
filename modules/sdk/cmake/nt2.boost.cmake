################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find and detect Boost libraries and setup the bootstrap macro
################################################################################
SET(Boost_ADDITIONAL_VERSIONS "1.45" "1.45.0" "1.46" "1.46.0" "1.46.1")
INCLUDE(FindBoost)
FIND_PACKAGE( Boost 1.46.0 )

IF(Boost_FOUND)
 SET(NT2_HAVE_BOOST TRUE)
ELSE()
 SET(NT2_HAVE_BOOST FALSE)
ENDIF()


