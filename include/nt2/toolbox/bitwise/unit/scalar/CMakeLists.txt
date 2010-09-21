##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  negif.cpp
  genmask.cpp
  selsub.cpp
  seladd.cpp
  select.cpp
  twopower.cpp
  shri.cpp
  shrai.cpp
  shli.cpp
  rshr.cpp
  rshl.cpp
  rror.cpp
  rrol.cpp
  ror.cpp
  rol.cpp
  reversebits.cpp
  popcnt.cpp
  lo.cpp
  hi.cpp
  firstbitunset.cpp
  firstbitset.cpp
  ffs.cpp
  bitwise_select.cpp
  bitwise_notand.cpp
  bitwise_andnot.cpp
  bitwise_ornot.cpp
  bitwise_notor.cpp
  bits.cpp
# List of scalar test files for toolbox bitwise
   )

##############################################################################
# For each filename
##############################################################################
FOREACH( EXAMPLE ${SOURCES})
  ############################################################################
  ## Build the executable filename from the example source filename
  ############################################################################
  STRING(REGEX REPLACE ".cpp" ".bitwise.scalar.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-bitwise.scalar.unit" TEST "${EXAMPLE}")

  ############################################################################
  ## Add as a target
  ############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)

  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()