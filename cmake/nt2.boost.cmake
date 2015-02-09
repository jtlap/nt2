################################################################################
#         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 - 2015 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#         Copyright 2012 - 2015 NumScale SAS
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find and detect Boost libraries
################################################################################
set(Boost_ADDITIONAL_VERSIONS "1.57")

if(NOT Boost_FOUND)
  find_package( Boost 1.57 QUIET )
  if(Boost_VERSION LESS 105700)
    message(STATUS "[nt2] Boost version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} not recent enough, needs 1.57.0")
    set(Boost_FOUND 0)
  endif()
  if(Boost_FOUND)
    message(STATUS "[nt2] Boost version: ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
  else()
    message(STATUS "[nt2] Boost NOT found")
  endif()
endif()
