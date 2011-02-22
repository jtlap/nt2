SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )
   
FIND_PACKAGE(Matlab)
IF(MATLAB_FOUND)

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
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE} libnt2_mw_mcc_component_data.c)
  INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})
  
  ADD_CUSTOM_COMMAND(OUTPUT libnt2_mw_mcc_component_data.c
                     COMMAND "${MATLAB_BIN_DIR}/mcc" -C -W lib:libnt2_mw eval)
  
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MX_LIBRARY})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${MATLAB_MCR_LIBRARY})
  ADD_DEPENDENCIES(matlab.scalar.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()

ELSE(MATLAB_FOUND)
    MESSAGE("Matlab not found")
ENDIF(MATLAB_FOUND)
