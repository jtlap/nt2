################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# This macros package everything needed to make a NT2 unit test for ctest
################################################################################

MACRO(MAKE_NT2_TEST FILENAME EXECUTABLE SUITE)
  ##############################################################################
  # Build target name from the executable name
  ##############################################################################
  STRING(REGEX REPLACE ".unit" "-unit" TEST "${EXECUTABLE}")
  
  ##############################################################################
  # Build executable from the files and link to nt2 components
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${FILENAME})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
  
  ADD_DEPENDENCIES(${SUITE} ${EXECUTABLE})
ENDMACRO(MAKE_NT2_TEST)

################################################################################
# This macros package everything needed to make a NT2 unit test for ctest with
# customizable compilation flags
################################################################################

MACRO(MAKE_NT2_TEST_WITH FILENAME EXECUTABLE SUITE FLAGS)
  ##############################################################################
  # Build target name from the executable name
  ##############################################################################
  STRING(REGEX REPLACE ".unit" "-unit" TEST "${EXECUTABLE}")
  
  ##############################################################################
  # Build executable from the files and link to nt2 components
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${FILENAME})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  
  SET_TARGET_PROPERTIES(${EXECUTABLE} PROPERTIES COMPILE_FLAGS ${FLAGS})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
  
  ADD_DEPENDENCIES(${SUITE} ${EXECUTABLE})
ENDMACRO(MAKE_NT2_TEST_WITH)
