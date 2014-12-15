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
  blas_dotu.cpp
  blas_nrm2.cpp
  blas_asum.cpp
  blas_i_amax.cpp
  blas_gemv.cpp
  blas_symv.cpp
  blas_hemv.cpp
  blas_trmv.cpp
  blas_trsv.cpp
  blas_ger.cpp
  blas_geru.cpp
  blas_syr.cpp
  blas_her.cpp
  blas_syr2.cpp
  blas_her2.cpp
  blas_gemm.cpp
  blas_symm.cpp
  blas_hemm.cpp
  blas_syrk.cpp
  blas_syr2k.cpp
  blas_herk.cpp
  blas_her2k.cpp
  blas_trmm.cpp
  blas_trsm.cpp
  blas_pack.cpp
  blas_unpack.cpp
  blas_hpmv.cpp
  blas_spmv.cpp
  blas_tpmv.cpp
  blas_tpsv.cpp
  )

nt2_module_add_tests(core.linalg.blas.unit ${SOURCES})
