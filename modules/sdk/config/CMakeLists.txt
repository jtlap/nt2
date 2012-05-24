################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

cmake_minimum_required(VERSION 2.6)

if(NOT DEFINED NT2_SOURCE_ROOT AND DEFINED ENV{NT2_SOURCE_ROOT})
  set(NT2_SOURCE_ROOT $ENV{NT2_SOURCE_ROOT})
endif()
if(NOT DEFINED NT2_ROOT AND DEFINED ENV{NT2_ROOT})
  set(NT2_ROOT $ENV{NT2_ROOT})
endif()
if(DEFINED NT2_SOURCE_ROOT)
  list(APPEND CMAKE_MODULE_PATH ${NT2_SOURCE_ROOT}/cmake)
endif()
if(DEFINED NT2_ROOT)
  list(APPEND CMAKE_MODULE_PATH ${NT2_ROOT}/cmake)
endif()

include(NT2Module)
nt2_module_main(sdk.config)
