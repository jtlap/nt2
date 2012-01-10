################################################################################
##         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
##         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
##
##          Distributed under the Boost Software License, Version 1.0.
##                 See accompanying file LICENSE.txt or copy at
##                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET(  SOURCES
  allocator.cpp
  buffer.cpp
  id.cpp
  index.cpp
  size.cpp
  storage_order.cpp
  shape.cpp
  sharing.cpp
  storage_duration.cpp
  storage_scheme.cpp
  alignment.cpp
  padding.cpp
  )

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set_property(SOURCE id.cpp PROPERTY COMPILE_FLAGS "-Wno-multichar")
endif()

nt2_module_add_tests(core.settings.unit ${SOURCES})
