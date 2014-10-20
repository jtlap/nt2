################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  extract.cpp
  insert.cpp
  aligned_load.cpp
  aligned_store.cpp
  stream.cpp
  load.cpp
  store.cpp
  slide.cpp
  splat.cpp
  )

nt2_module_add_tests(boost.simd.sdk.memory.scalar.unit ${SOURCES})

