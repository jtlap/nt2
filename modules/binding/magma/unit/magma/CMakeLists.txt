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
      gesv.cpp
      gesvx.cpp
      geqrf.cpp
      geqp3.cpp
      gemsv.cpp
      posv.cpp
      gesvd.cpp
      potrf.cpp
      sne.cpp
      gels.cpp
      sysv.cpp
   )

nt2_module_add_tests(binding.magma.linalg.unit ${SOURCES})
