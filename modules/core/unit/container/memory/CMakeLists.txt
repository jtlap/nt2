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
  buffer.cpp
  container.cpp
  container_id.cpp
  dimensions_of.cpp
  fixed_allocator.cpp
  iliffe_buffer.cpp
  padding.cpp
## List of scalar test files for toolbox core.memory
   )

nt2_module_add_tests(core.container.memory.unit ${SOURCES})
