SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )
   
FIND_PACKAGE(Matlab)

SET_SOURCE_FILES_PROPERTIES(lint2_mw.h HEADER_FILE_ONLY)

FIND_LIBRARY(NT2_MW_LIBRARY nt2_mw .)
  
IF(NOT MATLAB_FOUND)
  MESSAGE(FATAL_ERROR "Matlab not found")
ENDIF(NOT MATLAB_FOUND)

INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR} .)
  
ADD_CUSTOM_COMMAND(OUTPUT libnt2_mw.h ${NT2_MW_LIBRARY}
                   COMMAND "${MATLAB_BIN_DIR}/mcc" -B csharedlib:libnt2_mw feval)

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  ##**************************************************************************
  ## Build the executable filename from the example source filename
  ##**************************************************************************
  STRING(REGEX REPLACE ".cpp" ".matlab.scalar.unit" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-matlab.scalar.unit" TEST "${EXAMPLE}")

  ##**************************************************************************
  ## Add as a target
  ##**************************************************************************
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE} libnt2_mw.h)
  
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MX_LIBRARY})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MCR_LIBRARY})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${NT2_MW_LIBRARY})
  
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  ADD_DEPENDENCIES(matlab.scalar.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
