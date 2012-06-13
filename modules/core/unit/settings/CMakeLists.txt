################################################################################
##         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
##         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
##
##          Distributed under the Boost Software License, Version 1.0.
##                 See accompanying file LICENSE.txt or copy at
##                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
     alignment.cpp
     allocator.cpp
     buffer.cpp
     index.cpp
     size.cpp
     storage_order.cpp
     shape.cpp
     sharing.cpp
     storage_duration.cpp
     storage_scheme.cpp
   )

include(CheckCXXCompilerFlag)
nt2_module_add_tests(core.settings.unit ${SOURCES})
