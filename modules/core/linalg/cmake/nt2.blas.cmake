################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find BLAS and LAPACK
# - NT2_BLAS_VENDOR can be set to Intel, Goto2, Netlib, OpenBLAS or be empty
# - NT2_BLAS_ROOT specify a directory where libraries are. If using Intel,
#                 prefer setting MKLROOT instead.
# - NT2_BLAS_MULTICORE can be set to 1 or 0 to enable/disable multicore handling
#                      if supported by the BLAS implementation.
#                      if not set, defaults to 1 if computer is multicore.
# - NT2_BLAS_STATIC force usage of static variant of libraries.
#                   can be useful on some system to workaround issues with MKL
################################################################################
include(nt2.info)

set(NT2_BLAS_FOUND FALSE)

if(NT2_BLAS_STATIC)
  set(OLD_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.lib")
endif()

set(STATIC)
if(NT2_BLAS_STATIC)
  set(STATIC _static)
endif()

# Intel MKL
if(NT2_BLAS_VENDOR STREQUAL "Intel" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))

  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying Intel...")
  endif()

  # workaround for Ubuntu 13.10
  if(NOT DEFINED NT2_BLAS_STATIC)
    execute_process(COMMAND lsb_release -rs RESULT_VARIABLE RESULT_VAR OUTPUT_VARIABLE RESULT ERROR_QUIET)
    if(RESULT_VAR EQUAL 0 AND NOT RESULT VERSION_LESS 13.10)
      message(STATUS "[nt2.blas] Ubuntu 13.10+ detected, using static MKL as workaround")
      set(NT2_BLAS_STATIC 1 CACHE BOOL "Whether BLAS/LAPACK should be linked statically or not")
      set(OLD_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
      set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.lib")
      set(STATIC _static)
    endif()
  endif()

  set(MKLROOT $ENV{MKLROOT})
  if(NOT MKLROOT)
    set(MKLROOT /opt/intel/mkl)
  endif()

  set(NT2_BLAS_LIBRARIES)
  set(NT2_MKL_LIBRARY_DIR ${MKLROOT}/lib/)
  if(NT2_ARCH_X86_64)
    set(NT2_MKL_LIBRARY_SUFFIXES intel64)
    find_library(NT2_MKL_LP64${STATIC} NAMES mkl_intel_lp64_dll mkl_intel_lp64
                 PATHS ${NT2_MKL_LIBRARY_DIR}
                 PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                )
    set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_LP64${STATIC}})
  elseif(NT2_ARCH_MIC)
    set(NT2_MKL_LIBRARY_DIR ${NT2_BLAS_ROOT} ${MKLROOT}/lib/mic/)
    set(NT2_MKL_LIBRARY_SUFFIXES mic)

    set(NT2_MKL_LIBRARY_DIR $ENV{MKLROOT}/lib/)
    find_library(NT2_MKL_LP64${STATIC}
                 NAMES mkl_intel_lp64_dll mkl_intel_lp64
                 PATHS ${NT2_MKL_LIBRARY_DIR}
                 PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                )
    set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_LP64${STATIC}})
  else()
    set(NT2_MKL_LIBRARY_SUFFIXES ia32)
    set(NT2_MKL_LIBRARY_DIR ${NT2_BLAS_ROOT} ${MKLROOT}/lib/ia32)
    find_library(NT2_MKL_32${STATIC} NAMES mkl_intel_c_dll mkl_intel_c mkl_intel
                 PATHS ${NT2_MKL_LIBRARY_DIR}
                 PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                )
    set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_32${STATIC}})
  endif()

  if(NT2_MKL_LP64${STATIC} OR NT2_MKL_32${STATIC})
    if(NOT DEFINED NT2_BLAS_MULTICORE)
      nt2_module_tool(is_multicore RESULT_VARIABLE RESULT_VAR OUTPUT_QUIET)
      if(RESULT_VAR GREATER -1)
        set(NT2_BLAS_MULTICORE 1)
      endif()
    endif()
    if(NOT NT2_BLAS_MULTICORE)
      find_library(NT2_MKL_SEQ${STATIC} NAMES mkl_sequential_dll mkl_sequential
                   PATHS ${NT2_MKL_LIBRARY_DIR}
                   PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                  )
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_SEQ${STATIC}})
    else()
      # avoid re-checking for OpenMP every time
      if(NOT DEFINED OpenMP_CXX_FLAGS)
        find_package(OpenMP QUIET)
      endif()
      if(NT2_COMPILER_ICC OR NT2_COMPILER_MSVC OR NOT OpenMP_CXX_FLAGS)
        unset(NT2_MKL_GNU_THREAD${STATIC})
        find_library(NT2_MKL_INTEL_THREAD${STATIC} NAMES mkl_intel_thread_dll mkl_intel_thread
                     PATHS ${NT2_MKL_LIBRARY_DIR}
                     PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                    )
        file(TO_CMAKE_PATH "$ENV{LIBRARY_PATH}" LIBRARY_PATH)

        if(NT2_ARCH_MIC)
          set(TEMP_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
          set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so")
          find_library(NT2_INTEL_OMP${STATIC} NAMES libiomp5md iomp5md iomp5
                       PATHS ${CMAKE_FIND_ROOT_PATH}/compiler/lib/
                       PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                      )
          set(CMAKE_FIND_LIBRARY_SUFFIXES ${TEMP_CMAKE_FIND_LIBRARY_SUFFIXES})
        else()
          find_library(NT2_INTEL_OMP${STATIC} NAMES libiomp5md iomp5md iomp5
                       PATHS ${LIBRARY_PATH}
                       PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                      )
        endif()
        set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_INTEL_THREAD${STATIC}} ${NT2_INTEL_OMP${STATIC}})
      elseif(NT2_COMPILER_GCC_LIKE)
        unset(NT2_MKL_INTEL_THREAD${STATIC})
        unset(NT2_INTEL_OMP${STATIC})
        find_library(NT2_MKL_GNU_THREAD${STATIC} NAMES mkl_gnu_thread
                     PATHS ${NT2_MKL_LIBRARY_DIR}
                     PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                    )
        set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_GNU_THREAD${STATIC}})
        set(NT2_BLAS_LINK_FLAGS ${OpenMP_CXX_FLAGS})
      endif()
    endif()
    find_library(NT2_MKL_CORE${STATIC} NAMES mkl_core_dll mkl_core
                 PATHS ${NT2_MKL_LIBRARY_DIR}
                 PATH_SUFFIXES ${NT2_MKL_LIBRARY_SUFFIXES}
                )
    set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_CORE${STATIC}})
    if(UNIX)
        set(NT2_BLAS_LIBRARIES -Wl,--start-group ${NT2_BLAS_LIBRARIES} -Wl,--end-group)
        if(NT2_BLAS_STATIC)
          set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} -ldl)
        endif()
        set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} -lpthread)
      endif()

    if(NT2_MKL_CORE${STATIC})
      if(NT2_MKL_SEQ${STATIC} OR NT2_MKL_GNU_THREAD${STATIC} OR (NT2_MKL_INTEL_THREAD${STATIC} AND NT2_INTEL_OMP${STATIC}))
        set(NT2_BLAS_FOUND TRUE)
        set(NT2_LAPACK_FOUND TRUE)
      endif()
    endif()

  endif()

  if(NT2_BLAS_FOUND AND NOT DEFINED NT2_BLAS_VENDOR)
    set(NT2_BLAS_VENDOR Intel)
    message(STATUS "[nt2.blas] Intel found")
  endif()
endif()

if(NT2_BLAS_VENDOR STREQUAL "Goto2" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))
  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying Goto2...")
  endif()

  find_library(NT2_GOTO2${STATIC} NAMES goto2
               PATHS ${NT2_BLAS_ROOT})
  if(NT2_GOTO2${STATIC})
    set(NT2_BLAS_FOUND TRUE)
    set(NT2_BLAS_LIBRARIES ${NT2_GOTO2${STATIC}})

    if(NOT DEFINED NT2_BLAS_VENDOR)
      set(NT2_BLAS_VENDOR Goto2)
      message(STATUS "[nt2.linalg] Goto2 found")
    endif()
  endif()
endif()

if(NT2_BLAS_VENDOR STREQUAL "Netlib" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))
  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying Netlib...")
  endif()

  find_library(NT2_NETLIB${STATIC} NAMES blas_LINUX
               PATHS ${NT2_BLAS_ROOT})
  if(NT2_NETLIB)
    set(NT2_BLAS_FOUND TRUE)
    set(NT2_BLAS_LIBRARIES ${NT2_NETLIB${STATIC}})

    if(NOT DEFINED NT2_BLAS_VENDOR)
      set(NT2_BLAS_VENDOR Netlib)
      message(STATUS "[nt2.blas] Netlib found")
    endif()
  endif()
endif()

if(NT2_BLAS_VENDOR STREQUAL "Atlas" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))
  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying Atlas...")
  endif()

  find_library(NT2_ATLAS${STATIC} NAMES atlas
               PATHS ${NT2_BLAS_ROOT} )

  if(NT2_ATLAS${STATIC})
    set(NT2_BLAS_FOUND TRUE)
    set(NT2_BLAS_LIBRARIES ${NT2_ATLAS${STATIC}} -lblas -llapack -lgfortran)

    if(NOT DEFINED NT2_BLAS_VENDOR)
      set(NT2_BLAS_VENDOR Atlas)
      message(STATUS "[nt2.blas] Atlas found")
    endif()
  endif()
endif()

if(NT2_BLAS_VENDOR STREQUAL "OpenBLAS" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))
  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying OpenBLAS...")
  endif()

  find_library(NT2_OPENBLAS${STATIC} NAMES openblas
               PATHS ${NT2_BLAS_ROOT} /opt/OpenBLAS/lib)
  if(NT2_OPENBLAS${STATIC})
    set(NT2_BLAS_FOUND TRUE)
    set(NT2_LAPACK_FOUND TRUE)
    set(NT2_BLAS_LIBRARIES ${NT2_OPENBLAS${STATIC}})

    if(NOT DEFINED NT2_BLAS_VENDOR)
      set(NT2_BLAS_VENDOR OpenBLAS)
      message(STATUS "[nt2.blas] OpenBLAS found")
    endif()
  endif()
endif()

if(NOT NT2_BLAS_FOUND)

  if(NOT DEFINED NT2_BLAS_VENDOR)
    message(STATUS "[nt2.blas] trying built-in...")
  endif()

  find_library(BLAS_LIBRARY${STATIC} NAMES blas libblas PATHS ${NT2_BLAS_ROOT})
  if(BLAS_LIBRARY${STATIC})
    set(NT2_BLAS_FOUND 1)
    set(NT2_BLAS_LIBRARIES ${BLAS_LIBRARY${STATIC}})
  endif()

  if(NOT NT2_BLAS_FOUND)
    find_package(BLAS QUIET)
    set(NT2_BLAS_FOUND ${BLAS_FOUND})
    set(NT2_BLAS_LIBRARIES ${BLAS_LIBRARIES})
    set(NT2_BLAS_LINK_FLAGS ${BLAS_LINKER_FLAGS})
  endif()

  if(NT2_BLAS_FOUND AND NOT DEFINED NT2_BLAS_VENDOR)
    set(NT2_BLAS_VENDOR "")
    message(STATUS "[nt2.blas] built-in found")
  endif()

endif()

if(NOT NT2_LAPACK_FOUND) # Find lapack if not MKL
  message(STATUS "[nt2.linalg] looking for LAPACK...")

  find_library(LAPACK_LIBRARY${STATIC} NAMES lapack liblapack PATHS ${NT2_BLAS_ROOT})
  if(LAPACK_LIBRARY)
    set(NT2_LAPACK_FOUND 1)
    set(NT2_LAPACK_LIBRARIES ${LAPACK_LIBRARY${STATIC}})
  endif()

  if(NOT NT2_LAPACK_FOUND)
    find_package(LAPACK QUIET)
    set(NT2_LAPACK_FOUND ${LAPACK_FOUND})
    set(NT2_LAPACK_LIBRARIES ${LAPACK_LIBRARIES})
  endif()

  if(NT2_LAPACK_FOUND) # Find lapack if not MKL
    message(STATUS "[nt2.linalg] LAPACK found")
  endif()
endif()

set(NT2_BLAS_VENDOR ${NT2_BLAS_VENDOR} CACHE STRING "BLAS vendor (supported: \"Intel\", \"Goto2\", \"Netlib\" , \"Atlas\", \"OpenBLAS\")")
if(NOT NT2_BLAS_FOUND OR NOT NT2_LAPACK_FOUND)
  message(STATUS "[nt2.linalg] BLAS or LAPACK not found, if available please specify NT2_BLAS_ROOT or NT2_BLAS_VENDOR")
endif()

if(NT2_BLAS_STATIC)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${OLD_CMAKE_FIND_LIBRARY_SUFFIXES})
endif()
