################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

FIND_PACKAGE(NT2 COMPONENTS sdk)
FIND_PACKAGE(Matlab)
IF(NOT NT2_FOUND OR NOT MATLAB_FOUND)
  SET(NT2_MATLAB_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_MATLAB_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_MW_LIBRARY "libnt2_mw${CMAKE_SHARED_LIBRARY_SUFFIX}")

SET(NT2_MATLAB_DEPENDENCIES_INCLUDE_DIR ${NT2_INCLUDE_DIR} ${MATLAB_INCLUDE_DIR})
SET(NT2_MATLAB_DEPENDENCIES_LIBRARY_DIR ${NT2_LIBRARY_DIR} ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
SET(NT2_MATLAB_DEPENDENCIES_LIBRARIES ${NT2_LIBRARIES} ${MATLAB_MX_LIBRARY} ${MATLAB_MCR_LIBRARY} ${NT2_MW_LIBRARY})

IF(NT2_MATLAB_DEPENDENCIES_FOUND)
  IF(NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/libnt2_mw.h
  OR NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/${NT2_MW_LIBRARY})
    MESSAGE(STATUS "[nt2.matlab] generating libnt2_mw library...")
    IF(NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
      FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
    ENDIF()
    EXECUTE_PROCESS( COMMAND ${MATLAB_BIN_DIR}/mcc -B "csharedlib:libnt2_mw" feval
                     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/
                   )
  ENDIF()
ENDIF()
