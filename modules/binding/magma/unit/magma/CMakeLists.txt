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
      sv.cpp
      qrf.cpp
      qp3.cpp
      msv.cpp
   )

nt2_module_add_tests(binding.linalg.magma.unit ${SOURCES})
