##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  balance.cpp
  balance_result.cpp
  chol.cpp
  geneig.cpp
  geneig_result.cpp
  ldl_result.cpp
  lu.cpp
  lu_result.cpp
  qr.cpp
  qr_result.cpp
  schur_result.cpp
  svd_result.cpp
  symeig.cpp
  symeig_result.cpp
  )

nt2_module_add_tests(core.linalg.factorization.unit ${SOURCES})
