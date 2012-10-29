##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  all.cpp
  any.cpp
  as_integer.cpp
  as_floating.cpp
  as_signed.cpp
  as_unsigned.cpp
  behave_as.cpp
  downgrade.cpp
  enable_if_type.cpp
  factory_of.cpp
  is_fundamental.cpp
  is_iterator.cpp
  is_result_of_supported.cpp
  is_scalar.cpp
  is_signed.cpp
  is_unspecified.cpp
  make_integer.cpp
  make_floating.cpp
  primitive_of.cpp
  sign_of.cpp
  strip.cpp
  upgrade.cpp
  )

FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(boost.dispatch.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()


