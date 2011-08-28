SET( SOURCES
  sin.cpp
# List of scalar test files for toolbox matlab
   )

nt2_module_add_tests(matlab.scalar.unit ${SOURCES})
