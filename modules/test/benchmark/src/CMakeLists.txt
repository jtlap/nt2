################################################################################
#         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#         Copyright 2012 - 2013 MetaScale SAS
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(test.benchmark)

set ( SOURCES
      args.cpp
      priority.cpp
      speedup.cpp
      suite.cpp
    )

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-fvisibility=hidden)
endif()

nt2_module_add_library(nt2_bench ${SOURCES})
