################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(matlab)

SET(NT2_MW_LIBRARY "libnt2_mw${CMAKE_SHARED_LIBRARY_SUFFIX}")

IF(NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/libnt2_mw.h
OR NOT EXISTS ${LIBRARY_OUTPUT_PATH}/${NT2_MW_LIBRARY})
  MESSAGE(STATUS "[nt2.matlab] generating libnt2_mw library...")
  IF(NOT EXISTS ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
    FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/)
  ENDIF()
  IF(NOT EXISTS ${LIBRARY_OUTPUT_PATH})
    FILE(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
  ENDIF()
  EXECUTE_PROCESS( COMMAND ${MATLAB_BIN_DIR}/mcc -B "csharedlib:libnt2_mw" feval
                   WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH}
                 )
  FILE(RENAME ${LIBRARY_OUTPUT_PATH}/libnt2_mw.h ${PROJECT_BINARY_DIR}/include/nt2/toolbox/matlab/details/libnt2_mw.h)
ENDIF()

INSTALL( FILES ${LIBRARY_OUTPUT_PATH}/${NT2_MW_LIBRARY}
         DESTINATION ${NT2_INSTALL_LIBRARY_DIR}
         COMPONENT ${NT2_CURRENT_MODULE}
       )
