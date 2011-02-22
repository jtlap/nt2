# - this module looks for Matlab
# Defines:
#  MATLAB_ROOT:        root matlab directory
#  MATLAB_BIN_DIR:     matlab binaries directory
#  MATLAB_INCLUDE_DIR: include path for mex.h, engine.h
#  MATLAB_RUNTIME_DIR: matlab runtime directory
#  MATLAB_LIB_DIR:     matlab libraries directory

#  MATLAB_MEX_LIBRARY: path to libmex.lib
#  MATLAB_MX_LIBRARY:  path to libmx.lib
#  MATLAB_ENG_LIBRARY: path to libeng.lib
#  MATLAB_MCR_LIBRARY: path to libmwmclmcrrt.lib

#=============================================================================
# Copyright 2011 Mathias Gaunard
#=============================================================================

SET(MATLAB_FOUND 0)

IF(NOT MATLAB_ROOT AND NOT $ENV{MATLAB_ROOT} STREQUAL "")
  SET(MATLAB_ROOT $ENV{MATLAB_ROOT})
ENDIF(NOT MATLAB_ROOT AND NOT $ENV{MATLAB_ROOT} STREQUAL "")

IF(WIN32)

  IF(NOT MATLAB_ROOT)
    SET(MATLAB_ROOT "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\7.0;MATLABROOT]")
  ENDIF(NOT MATLAB_ROOT)

  IF(${CMAKE_GENERATOR} MATCHES "Visual Studio 6")
    SET(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win32/microsoft/msvc60")
  ELSE(${CMAKE_GENERATOR} MATCHES "Visual Studio 6")
    IF(${CMAKE_GENERATOR} MATCHES "Visual Studio 7")
      # Assume people are generally using 7.1,
      # if using 7.0 need to link to: ../extern/lib/win32/microsoft/msvc70
      SET(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win32/microsoft/msvc71")
    ELSE(${CMAKE_GENERATOR} MATCHES "Visual Studio 7")
      IF(${CMAKE_GENERATOR} MATCHES "Borland")
        # Same here, there are also: bcc50 and bcc51 directories
        SET(MATLAB_LIB_DIR "${MATLAB_ROOT}/extern/lib/win32/microsoft/bcc54")
      ELSE(${CMAKE_GENERATOR} MATCHES "Borland")
        IF(MATLAB_FIND_REQUIRED)
          MESSAGE(FATAL_ERROR "Generator not compatible: ${CMAKE_GENERATOR}")
        ENDIF(MATLAB_FIND_REQUIRED)
      ENDIF(${CMAKE_GENERATOR} MATCHES "Borland")
    ENDIF(${CMAKE_GENERATOR} MATCHES "Visual Studio 7")
  ENDIF(${CMAKE_GENERATOR} MATCHES "Visual Studio 6")

ELSE( WIN32 )

  SET(NAMES matlab matlab-7sp1 redhat-matlab)
  SET(DIRECTORIES /usr/local /opt $ENV{HOME})
  
  FOREACH(DIR ${DIRECTORIES})
    FOREACH(NA ${NAMES})
        IF(NOT MATLAB_ROOT AND EXISTS "${DIR}/${NA}")
            SET(MATLAB_ROOT "${DIR}/${NA}")
        ENDIF(NOT MATLAB_ROOT AND EXISTS "${DIR}/${NA}")
    ENDFOREACH()
  ENDFOREACH()

ENDIF(WIN32)

# This is common to UNIX and Win32:

IF(MATLAB_ROOT)
  SET(MATLAB_BIN_DIR "${MATLAB_ROOT}/bin")
ENDIF(MATLAB_ROOT)

IF(MATLAB_ROOT AND NOT MATLAB_LIB_DIR)
  IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # Regular x86
    SET(MATLAB_LIB_DIR "${MATLAB_ROOT}/bin/glnx86")
  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # AMD64:
    SET(MATLAB_LIB_DIR "${MATLAB_ROOT}/bin/glnxa64")
  ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
ENDIF(MATLAB_ROOT AND NOT MATLAB_LIB_DIR)

IF(MATLAB_ROOT AND NOT MATLAB_RUNTIME_DIR)
  IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # Regular x86
    SET(MATLAB_RUNTIME_DIR "${MATLAB_ROOT}/runtime/glnx86")
  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # AMD64:
    SET(MATLAB_RUNTIME_DIR "${MATLAB_ROOT}/runtime/glnxa64")
  ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
ENDIF(MATLAB_ROOT AND NOT MATLAB_RUNTIME_DIR)

FIND_PATH(MATLAB_INCLUDE_DIR
  "mex.h"
  "${MATLAB_ROOT}/extern/include"
)

FIND_LIBRARY(MATLAB_MEX_LIBRARY
  mex
  ${MATLAB_LIB_DIR}
)
FIND_LIBRARY(MATLAB_MX_LIBRARY
  mx
  ${MATLAB_LIB_DIR}
)
FIND_LIBRARY(MATLAB_ENG_LIBRARY
  eng
  ${MATLAB_LIB_DIR}
)
FIND_LIBRARY(MATLAB_MCR_LIBRARY
  mwmclmcrrt
  ${MATLAB_RUNTIME_DIR}
)

IF(MATLAB_INCLUDE_DIR)
  SET(MATLAB_FOUND 1)
ENDIF(MATLAB_INCLUDE_DIR)

MARK_AS_ADVANCED(
  MATLAB_FOUND
  MATLAB_ROOT
  MATLAB_INCLUDE_DIR
  MATLAB_BIN_DIR
  MATLAB_LIB_DIR
  MATLAB_RUNTIME_DIR
  MATLAB_MEX_LIBRARY
  MATLAB_MX_LIBRARY
  MATLAB_ENG_LIBRARY
  MATLAB_MCR_LIBRARY
)

