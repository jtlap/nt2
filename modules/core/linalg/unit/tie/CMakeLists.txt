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
     chol.cpp
     full_lu_solve.cpp
     full_qr_solve.cpp
#     geneig.cpp
     linsolve.cpp
     lsq_lse_solve.cpp
     lu.cpp
     planerot.cpp
     qr.cpp
     qrdelete.cpp
     qrinsert.cpp
     rref.cpp
     schur.cpp
     svd.cpp
     svd_solve.cpp
     symeig.cpp
     tiepb.cpp
     tr_solve.cpp
   )

nt2_module_add_tests(core.linalg.tie.unit ${SOURCES})

