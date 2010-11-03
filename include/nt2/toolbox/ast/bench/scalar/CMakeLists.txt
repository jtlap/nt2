##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  gamma.cpp
  log1p.cpp
  cbrt.cpp
  exp.cpp
  erfc.cpp
  erf.cpp
  lgamma.cpp
  asinh.cpp
  acosh.cpp
  rint.cpp
  log.cpp
  atanh.cpp
  expm1.cpp
# List of scalar test files for toolbox ast
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  ##**************************************************************************
  ## Build the executable filename from the example source filename
  ##**************************************************************************
  STRING(REGEX REPLACE ".cpp" ".ast.scalar.bench" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-ast.scalar.bench" TEST "${EXAMPLE}")

  ##**************************************************************************
  ## Add as a target
  ##**************************************************************************
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ast)


ENDFOREACH()