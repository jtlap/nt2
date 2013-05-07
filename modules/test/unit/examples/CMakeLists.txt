##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  test.cpp
  test_error.cpp
  test_assert.cpp
  test_throw.cpp
  test_no_throw.cpp
  test_no_assert.cpp
  test_case.cpp
  test_case_tpl.cpp
  test_type_expr.cpp
  test_type_info.cpp
  test_type_is.cpp
  test_equal.cpp
  test_not_equal.cpp
  test_greater.cpp
  test_greater_equal.cpp
  test_lesser.cpp
  test_lesser_equal.cpp
  )

FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_example(test.unit.${EXAMPLE}.sample ${EXAMPLE}.cpp)
ENDFOREACH()


