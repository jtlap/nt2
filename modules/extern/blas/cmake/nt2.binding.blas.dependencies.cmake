################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
include(nt2.blas)
if(NOT NT2_BLAS_FOUND)
  set(NT2_EXTERN.BLAS_DEPENDENCIES_FOUND 0)
else()
  set ( NT2_EXTERN.BLAS_DEPENDENCIES_LIBRARIES ${NT2_BLAS_LIBRARIES})
  set ( NT2_EXTERN.BLAS_DEPENDENCIES_EXTRA
        boost.dispatch
        boost.simd.base
        boost.simd.sdk
        core.base
        core.container.table
        core.extractive
        core.generative
        core.random
        core.reduction
        core.restructuring
        core.sdk
        core.swar
        sdk.config
        sdk.error
        sdk.functor
        sdk.meta
        type.complex.sdk
      )

endif()

FIND_LIBRARY(BLAS_LIBRARY blas)
IF(BLAS_LIBRARY MATCHES "NOTFOUND$")
  SET(NT2_EXTERN.BLAS_DEPENDENCIES_FOUND 0)
ELSE()
  SET(NT2_EXTERN.BLAS_DEPENDENCIES_FOUND 1)
ENDIF()

SET(NT2_EXTERN.BLAS_DEPENDENCIES_LIBRARIES ${BLAS_LIBRARY})
SET(NT2_EXTERN.BLAS_DEPENDENCIES_EXTRA core.base)
