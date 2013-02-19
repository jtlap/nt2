##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  binomial.cpp
  cauchy.cpp
  chebspec.cpp
  chebvand.cpp
  chow.cpp
  circul.cpp
  clement.cpp
  compar.cpp
  condex.cpp
  cycol.cpp
  dorr.cpp
  dramadah.cpp
  fiedler.cpp
  forsythe.cpp
  frank.cpp
  gcdmat.cpp
  gearmat.cpp
  grcar.cpp
  hadamard.cpp
  hankel.cpp
  hilb.cpp
  invhilb.cpp
  jordbloc.cpp
  magic.cpp
  minij.cpp
  pascal.cpp
  toeplitz.cpp
  tridiag.cpp
  triw.cpp
  vandermonde.cpp
  )

nt2_module_add_tests(core.linalg.functions.unit ${SOURCES})
