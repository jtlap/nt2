##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  array_buffer.cpp
  array_buffer_non_pod.cpp
  buffer.cpp
  buffer_non_pod.cpp
  composite_buffer.cpp
  composite_reference.cpp
  container.cpp
  container_non_pod.cpp
  composite_container.cpp
  fixed_allocator.cpp
## List of scalar test files for toolbox core.memory
   )

nt2_module_add_tests(core.sdk.memory.unit ${SOURCES})
