##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET(  SOURCES
      lu.cpp
      lu2.cpp
      lu3.cpp
      qr.cpp
      qr2_1.cpp
      qr2_2.cpp
      qr3_1.cpp
      qr3_2.cpp
      linsolve.cpp
   )

nt2_module_add_tests(core.linalg.factorization.table.bench ${SOURCES})
