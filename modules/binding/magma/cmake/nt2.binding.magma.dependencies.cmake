################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

set(MAGMA_FOUND 0)
if(DEFINED MAGMA_CXX_FLAGS AND NOT MAGMA_CXX_FLAGS)
set(MAGMA_FOUND 0)
else()

if(NOT DEFINED MAGMA_ROOT AND DEFINED ENV{MAGMA_ROOT})
set(MAGMA_ROOT $ENV{MAGMA_ROOT})
endif()

  # try to find libmagma
  find_library( MAGMA_MAGMA_LIBRARY
    NAMES magma
    PATHS ${MAGMA_ROOT}/lib
  )

  # try to find libmagmablas
  find_library( MAGMA_MAGMABLAS_LIBRARY
    NAMES magmablas
    PATHS ${MAGMA_ROOT}/lib
  )

  # try to find Intel C Runtime (if MAGMA was built with ICC)
  include(nt2.info)
  if(NT2_ARCH_X86_64)
  set(NT2_INTEL_LIBRARY_SUFFIXES intel64)
  else()
  set(NT2_INTEL_LIBRARY_SUFFIXES ia32)
  endif()

  if(NT2_BLAS_VENDOR STREQUAL "Intel" OR (NOT DEFINED NT2_BLAS_VENDOR AND NOT NT2_BLAS_FOUND) )

  if(NOT DEFINED INTEL_ROOT)
  set(INTEL_ROOT /opt/intel/composerxe)
  endif()

  find_library( INTEL_RC_LIBRARY
    NAMES irc
    PATHS ${INTEL_ROOT}/lib
    PATH_SUFFIXES ${NT2_INTEL_LIBRARY_SUFFIXES}
  )

  find_library( INTEL_OMP_LIBRARY
    NAMES iomp5
    PATHS ${INTEL_ROOT}/lib
    PATH_SUFFIXES ${NT2_INTEL_LIBRARY_SUFFIXES}
  )

  else()

  if(DEFINED OpenMP_CXX_FLAGS AND NOT OpenMP_CXX_FLAGS)
  set(OPENMP_FOUND 0)
  else()
  find_package(OpenMP QUIET)
  endif()

  endif()

  # CUDA-related stuff
  find_package(CUDA)
  set(CUBLAS_LIBRARY ${CUDA_CUBLAS_LIBRARIES})
  set(CUDART_LIBRARY ${CUDA_CUDART_LIBRARY})
  set(CUBLAS_HEADER ${CUDA_INCLUDE_DIRS})

  # try find magma.h
  find_path(  MAGMA_MAGMA_HEADER
    NAMES magma.h
    PATHS ${MAGMA_ROOT}/include
  )

  # try find common_magma.h
  find_path(  MAGMA_COMMON_HEADER
    NAMES common_magma.h
    PATHS /usr/local/control /usr/control ${MAGMA_ROOT}/control
  )

  # try find common_magma.h
  find_path(  CUDA_ERROR_HEADER
    NAMES error.h
    PATHS /usr/local/control /usr/control ${MAGMA_ROOT}/interface_cuda
  )

  # if everything is there ...
  if(MAGMA_MAGMA_LIBRARY AND MAGMA_MAGMA_HEADER
  AND CUBLAS_LIBRARY AND CUDART_LIBRARY AND CUBLAS_HEADER AND MAGMA_COMMON_HEADER )
  set(MAGMA_FOUND 1)
  set(MAGMA_INCLUDE_PATH "${MAGMA_MAGMA_HEADER}/" "${MAGMA_COMMON_HEADER}/" "${CUDA_ERROR_HEADER}/")
  set(MAGMA_CXX_FLAGS "-DNT2_USE_MAGMA -DHAVE_CUBLAS")
  set(MAGMA_LIBRARY ${MAGMA_MAGMA_LIBRARY} ${CUDART_LIBRARY} ${CUBLAS_LIBRARY})
  if(MAGMA_MAGMABLAS_LIBRARY)
  list(APPEND MAGMA_LIBRARY ${MAGMA_MAGMABLAS_LIBRARY})
  endif()
  if(INTEL_RC_LIBRARY AND INTEL_OMP_LIBRARY)
  list(APPEND MAGMA_LIBRARY ${INTEL_RC_LIBRARY} ${INTEL_OMP_LIBRARY})
  elseif(OPENMP_FOUND)
  list(APPEND MAGMA_LIBRARY ${OpenMP_CXX_FLAGS})
  endif()
  set(CUDA_INCLUDE_PATH "${CUBLAS_HEADER}/")
  endif()
  endif()

  set(NT2_BINDING.MAGMA_DEPENDENCIES_FOUND              ${MAGMA_FOUND})
  set(NT2_BINDING.MAGMA_COMPILE_FLAGS               ${MAGMA_CXX_FLAGS})
  set(NT2_BINDING.MAGMA_DEPENDENCIES_INCLUDE_DIR ${MAGMA_INCLUDE_PATH} ${CUDA_INCLUDE_PATH})
  set(NT2_BINDING.MAGMA_DEPENDENCIES_LIBRARIES        ${MAGMA_LIBRARY})

  set(  NT2_BINDING.MAGMA_DEPENDENCIES_EXTRA
    boost.dispatch
    boost.simd.base
    core.base
    core.container.table
    core.exponential
    core.generative
    core.linalg
    core.reduction
    core.restructuring
    core.sdk
  )
