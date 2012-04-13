################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(CMAKE_MODULE_PATH ${NT2_DIR})
if(EXISTS ${NT2_DIR}/../CMakeLists.txt)
  set(NT2_SOURCE_ROOT ${NT2_DIR}/..)
else()
  set(NT2_ROOT ${NT2_DIR}/..)
endif()

include(FindNT2)
