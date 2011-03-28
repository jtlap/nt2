SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )

##****************************************************************************
# For each filename
##****************************************************************************
FOREACH( EXAMPLE ${SOURCES})
  STRING(REGEX REPLACE ".cpp" "" EXAMPLE ${EXAMPLE})
  nt2_module_add_unit(matlab.scalar.${EXAMPLE}.unit ${EXAMPLE}.cpp)
ENDFOREACH()
