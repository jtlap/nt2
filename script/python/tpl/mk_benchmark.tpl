
SET( SOURCES
# <INCLUDE> PLEASE DON'T MODIFY BETWEEN THESE TAGS
# <\INCLUDE>
   )	


################################################################################
# For each filename
################################################################################
FOREACH( EXAMPLE ${SOURCES})
  ##############################################################################
  # Build the executable filename from the example source filename
  ##############################################################################
  STRING(REGEX REPLACE ".cpp" ".test" EXECUTABLE "${EXAMPLE}")
  STRING(REGEX REPLACE ".cpp" "-test" TEST "${EXAMPLE}")

  ##############################################################################
  # Add as a target
  ##############################################################################
  ADD_EXECUTABLE(${EXECUTABLE} ${EXAMPLE})
  TARGET_LINK_LIBRARIES(${EXECUTABLE} nt2)
ENDFOREACH()
