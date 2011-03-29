##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  asech1m.cpp
  sinhc.cpp
  tanh.cpp
  sinh.cpp
  sech.cpp
  csch.cpp
  coth.cpp
  cosh.cpp
  atanh.cpp
  asinh.cpp
  asech.cpp
  acsch.cpp
  acoth.cpp
  acosh.cpp
# List of scalar test files for toolbox hyperbolic
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(hyperbolic.scalar.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
