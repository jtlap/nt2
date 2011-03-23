SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )

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
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  
  TARGET_LINK_LIBRARIES(${EXECUTABLE} ${NT2_MATLAB_DEPENDENCIES_LIBRARIES})

  ADD_DEPENDENCIES(matlab.scalar.unit ${EXECUTABLE})
  ADD_TEST(${TEST} ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
ENDFOREACH()
