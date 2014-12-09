##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2013 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET ( SOURCES
  blas_rotg.cpp
  blas_rot.cpp
  blas_rotmg.cpp
  blas_rotm.cpp
  blas_scal.cpp
  blas_swap.cpp
  blas_copy.cpp
  blas_axpy.cpp
  blas_dot.cpp
  blas_nrm2.cpp
  blas_asum.cpp
  blas_i_amax.cpp
  blas_gemv.cpp
  blas_symv.cpp
  blas_trmv.cpp
  blas_trsv.cpp
  blas_ger.cpp
  blas_geru.cpp
  blas_syr.cpp
  blas_syr2.cpp
  )

nt2_module_add_tests(core.linalg.blas.unit ${SOURCES})
