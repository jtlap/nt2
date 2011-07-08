
################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

SET( SOURCES
  sum.cpp
  second.cpp
  prod.cpp
  posmin.cpp
  posmax.cpp
  nbtrue.cpp
  minimum.cpp
  maximum.cpp
  hmsb.cpp
  first.cpp
  dot.cpp
  at_i.cpp
  any.cpp
  all.cpp
# List of simd test files for toolbox reduction
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_cover(reduction.simd.${EXAMPLE}.cover ${EXAMPLE}.cpp)
ENDFOREACH()

