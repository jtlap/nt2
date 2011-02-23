SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )
   
FIND_PACKAGE(Matlab)

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
  SET_SOURCE_FILES_PROPERTIES(lint2_mw.h HEADER_FILE_ONLY)
  
  IF(NOT MATLAB_FOUND)
    MESSAGE(SEND_ERROR "Matlab not found")
  ELSE(NOT MATLAB_FOUND)
    INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR} .)
  
    ADD_CUSTOM_COMMAND(OUTPUT libnt2_mw.h
                       COMMAND "${MATLAB_BIN_DIR}/mcc" -B csharedlib:libnt2_mw feval)
  
    TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MX_LIBRARY})
    TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MCR_LIBRARY})
  ENDIF(NOT MATLAB_FOUND)
    
  FIND_LIBRARY(NT2_MW_LIBRARY nt2_mw .)
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${NT2_MW_LIBRARY})
  
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  ADD_DEPENDENCIES(matlab.scalar.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
