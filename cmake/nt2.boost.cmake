################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find and detect Boost libraries
################################################################################
set(Boost_ADDITIONAL_VERSIONS "1.48")

if(NOT Boost_FOUND)
  # Putting those in the cache is a bad idea, removing them
  unset(Boost_VERSION CACHE)
  unset(Boost_LIB_VERSION CACHE)

  find_package( Boost 1.48.0 QUIET )
  if(Boost_VERSION LESS 104800)
    message(STATUS "[nt2] Boost version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION} not recent enough, needs 1.48.0")
    set(Boost_FOUND 0)
  endif()
  if(Boost_FOUND)
    message(STATUS "[nt2] Boost version: ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
  else()
    message(STATUS "[nt2] Boost NOT found")
  endif()
endif()
