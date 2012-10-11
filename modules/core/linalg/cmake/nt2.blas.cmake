################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
################################################################################
# Find the Blas
################################################################################
include(nt2.info)

set(NT2_BLAS_FOUND FALSE)

  # Intel MKL
  if(NT2_BLAS_VENDOR STREQUAL "Intel" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND))

    if(NOT DEFINED NT2_BLAS_VENDOR)
      message(STATUS "[nt2.blas] trying Intel...")
    endif()

    if(NT2_ARCH_X86_64)
      set(NT2_MKL_LIBRARY_DIR ${NT2_BLAS_ROOT} /opt/intel/mkl/lib/intel64)
      find_library(NT2_MKL_LP64 NAMES mkl_intel_lp64 mkl_intel_lp64_dll
                   PATHS ${NT2_MKL_LIBRARY_DIR}
                  )
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_LP64})
    else()
      set(NT2_MKL_LIBRARY_DIR ${NT2_BLAS_ROOT} /opt/intel/mkl/lib/ia32)
      find_library(NT2_MKL_32 NAMES mkl_intel mkl_intel_c_dll
                   PATHS ${NT2_MKL_LIBRARY_DIR}
                  )
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_32})
    endif()

    if(NT2_MKL_LP64 OR NT2_MKL_32)

      nt2_module_tool(is_multicore RESULT_VARIABLE RESULT_VAR OUTPUT_QUIET)
      if(RESULT_VAR EQUAL -1 OR RESULT_VAR EQUAL 1)
        set(NT2_ARCH_MULTICORE FALSE)
        find_library(NT2_MKL_SEQ NAMES mkl_sequential mkl_sequential_dll
                     PATHS ${NT2_MKL_LIBRARY_DIR}
                    )
        set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_SEQ})
      else()
        if(NT2_COMPILER_ICC)
          find_library(NT2_MKL_INTEL_THREAD NAMES mkl_intel_thread mkl_intel_thread_dll
                       PATHS ${NT2_MKL_LIBRARY_DIR}
                      )
          set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_INTEL_THREAD})
          if(UNIX)
            set(NT2_BLAS_LINK_FLAGS "-openmp")
          elseif(WIN32)
            set(NT2_BLAS_LINK_FLAGS "/Qopenmp")
          endif()
          set(NT2_ARCH_MULTICORE TRUE)
        elseif(NT2_COMPILER_MSVC)
          find_library(NT2_MKL_INTEL_THREAD NAMES mkl_intel_thread_dll
                       PATHS ${NT2_MKL_LIBRARY_DIR}
                      )
          set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_ICC_LIB_ROOT}/libiomp5md.lib)
        elseif(NT2_COMPILER_GCC_LIKE)
          find_library(NT2_MKL_GNU_THREAD NAMES mkl_gnu_thread
                       PATHS ${NT2_MKL_LIBRARY_DIR}
                      )
          set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_GNU_THREAD})
          # avoid re-checking for OpenMP every time
          if(NOT DEFINED OpenMP_CXX_FLAGS)
            find_package(OpenMP QUIET)
          endif()
          set(NT2_BLAS_LINK_FLAGS ${OpenMP_CXX_FLAGS})
        endif()
      endif()

      if(UNIX)
        find_package(Threads)
        set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
      endif()

      find_library(NT2_MKL_CORE NAMES mkl_core mkl_core_dll
                   PATHS ${NT2_MKL_LIBRARY_DIR}
                  )
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_MKL_CORE})

      if(NT2_MKL_SEQ AND NT2_MKL_CORE)
        set(NT2_BLAS_FOUND TRUE)
        set(NT2_LAPACK_FOUND TRUE)
      elseif(NT2_MKL_GNU_THREAD OR NT2_MKL_INTEL_THREAD)
        if(NT2_MKL_CORE)
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

    find_library(NT2_GOTO2 NAMES goto2
                 PATHS ${NT2_BLAS_ROOT})
    if(NT2_GOTO2)
      set(NT2_BLAS_FOUND TRUE)
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_GOTO2})

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

    find_library(NT2_NETLIB NAMES blas_LINUX
                 PATHS ${NT2_BLAS_ROOT})
    if(NT2_NETLIB)
      set(NT2_BLAS_FOUND TRUE)
      set(NT2_BLAS_LIBRARIES ${NT2_BLAS_LIBRARIES} ${NT2_NETLIB})

      if(NOT DEFINED NT2_BLAS_VENDOR)
        set(NT2_BLAS_VENDOR Netlib)
        message(STATUS "[nt2.blas] Netlib found")
      endif()
    endif()
  endif()

  if(NOT NT2_BLAS_FOUND) # TODO : Other support if findBlas failed

    if(NOT DEFINED NT2_BLAS_VENDOR)
      message(STATUS "[nt2.blas] trying built-in...")
    endif()

    find_package(BLAS QUIET)
    set(NT2_BLAS_FOUND ${BLAS_FOUND})
    set(NT2_BLAS_LIBRARIES ${BLAS_LIBRARIES})
    set(NT2_BLAS_LINK_FLAGS ${BLAS_LINKER_FLAGS})

    if(BLAS_FOUND AND NOT DEFINED NT2_BLAS_VENDOR)
      set(NT2_BLAS_VENDOR "")
      message(STATUS "[nt2.blas] built-in found")
    endif()

  endif()

  if(NOT NT2_LAPACK_FOUND) # Find lapack if not MKL
    message(STATUS "[nt2.linalg] looking for LAPACK...")
    find_package(LAPACK QUIET)
    set(NT2_LAPACK_FOUND ${LAPACK_FOUND})
    set(NT2_LAPACK_LIBRARIES ${LAPACK_LIBRARIES})

    if(NT2_LAPACK_FOUND) # Find lapack if not MKL
      message(STATUS "[nt2.linalg] LAPACK found")
    endif()
  endif()

  set(NT2_BLAS_VENDOR ${NT2_BLAS_VENDOR} CACHE STRING "BLAS vendor (supported: \"Intel\", \"Goto2\", \"Netlib\")")
  if(NOT NT2_BLAS_FOUND OR NOT NT2_LAPACK_FOUND)
    message(STATUS "[nt2.linalg] BLAS or LAPACK not found, if available please specify NT2_BLAS_ROOT or NT2_BLAS_VENDOR")
  endif()
