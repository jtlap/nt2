##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2013 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET ( SOURCES
      getrf.cpp
      getri.cpp
      geqrf.cpp
      geqp3.cpp
      gqr.cpp
      mqr.cpp
      laswp.cpp
      gesv.cpp
      gesvx.cpp
      gels.cpp
      gelsy.cpp
      gecon.cpp
      gemsv.cpp
      clinsolve.cpp
      plinsolve.cpp
      mlinsolve.cpp
      sysvx.cpp
      posv.cpp
      langb.cpp
      gbsv.cpp
      gesvd.cpp
      potrf.cpp
      trsm.cpp
      sne.cpp
   )

nt2_module_add_tests(core.linalg.lapack.unit ${SOURCES})
