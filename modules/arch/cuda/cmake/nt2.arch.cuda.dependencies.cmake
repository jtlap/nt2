################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
find_package(CUDA)

IF(CUDA_FOUND)
set(NT2_ARCH.CUDA_COMPILE_FLAGS "-DNT2_HAS_CUDA")
set(CUBLAS_LIBRARY ${CUDA_CUBLAS_LIBRARIES})
set(CUDART_LIBRARY ${CUDA_CUDART_LIBRARY})
set(CUBLAS_HEADER ${CUDA_INCLUDE_DIRS})
set(NT2_ARCH.CUDA_DEPENDENCIES_INCLUDE_DIR ${CUDA_INCLUDE_DIRS})
set(NT2_ARCH.CUDA_DEPENDENCIES_LIBRARIES  ${CUDA_CUDART_LIBRARY} ${CUBLAS_LIBRARY})
ENDIF(CUDA_FOUND)

set(NT2_ARCH.CUDA_DEPENDENCIES_FOUND ${CUDA_FOUND})

set(  NT2_ARCH.CUDA_DEPENDENCIES_EXTRA
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

