SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )
   
FIND_PACKAGE(Matlab REQUIRED)

SET(NT2_MW_LIBRARY "libnt2_mw${CMAKE_SHARED_LIBRARY_SUFFIX}")

INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
LINK_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

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
