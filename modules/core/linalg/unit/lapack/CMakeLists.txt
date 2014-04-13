##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2013 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET ( SOURCES
      trf.cpp
      tri.cpp
      qrf.cpp
      qp3.cpp
      gqr.cpp
      mqr.cpp
      laswp.cpp
      swap.cpp
      sv.cpp
      svx.cpp
      ls.cpp
      lsy.cpp
      gecon.cpp
      msv.cpp
      clinsolve.cpp
      plinsolve.cpp
      mlinsolve.cpp
      ysvx.cpp
      posv.cpp
      langb.cpp
      bsv.cpp
      gesvd.cpp
      potrf.cpp
      trsm.cpp
      sne.cpp
   )

nt2_module_add_tests(core.linalg.lapack.unit ${SOURCES})
