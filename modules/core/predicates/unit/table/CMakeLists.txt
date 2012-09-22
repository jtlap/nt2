##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  iscolumn.cpp
  isdiagonal.cpp
  isempty.cpp
  isequal.cpp
  isequaln.cpp
  isexpandable_to.cpp
  isfloating.cpp
  ishermitian.cpp
  isinside.cpp
  isinteger.cpp
  ismatrix.cpp
  isreal.cpp
  isrow.cpp
  isscalar.cpp
  issorted.cpp
  issquare.cpp
  issymetric.cpp
  istriangular.cpp
  istril.cpp
  istriu.cpp
  isulpequal.cpp
  isvectoralong.cpp
  isvector.cpp
# List of table test files for toolbox predicates
   )

nt2_module_add_tests(core.predicates.table.unit ${SOURCES})
