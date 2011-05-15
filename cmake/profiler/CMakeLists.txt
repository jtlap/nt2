################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Template profiler rules and macros
################################################################################

################################################################################
# Find and detect Boost libraries
################################################################################
SET(Boost_ADDITIONAL_VERSIONS "1.45" "1.45.0" "1.46" "1.46.0" "1.46.1")
INCLUDE(FindBoost)
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE( Boost 1.46.0 COMPONENTS regex)

################################################################################
# Add the target to build filter and postprocess
################################################################################
ADD_CUSTOM_TARGET( template.profiler )
ADD_EXECUTABLE( template.profiler.filter      filter.cpp      )

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ADD_EXECUTABLE( template.profiler.postprocess postprocess.cpp )
target_link_libraries(template.profiler.postprocess ${Boost_LIBRARIES})

ADD_DEPENDENCIES(template.profiler template.profiler.filter      )   
ADD_DEPENDENCIES(template.profiler template.profiler.postprocess )

################################################################################
# Make a macro to compile foo and profile it
################################################################################

