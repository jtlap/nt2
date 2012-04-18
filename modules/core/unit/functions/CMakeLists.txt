##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  colon.cpp
  iscolumn.cpp
  isempty.cpp
  ismatrix.cpp
  isrow.cpp
  isscalar.cpp
  isvector.cpp
  length.cpp
  linspace.cpp
  first_last_index.cpp
  ndims.cpp
  numel.cpp
  ones.cpp
  reshape.cpp
  squeeze.cpp
  ind2sub.cpp
  sub2ind.cpp
  sub2sub.cpp
  size.cpp
  zeros.cpp
  issquare.cpp
  issymetric.cpp
  ishermitian.cpp
  istriangular.cpp
  istril.cpp
  istriu.cpp
  eye.cpp
  triu.cpp
  tril.cpp
  band.cpp
  tri1u.cpp
  tri1l.cpp
  ric.cpp
  rif.cpp
  rows.cpp
  resize.cpp
  expand.cpp 
  streaming.cpp
  cic.cpp
  cif.cpp
  cols.cpp
  colvect.cpp
  rowvect.cpp
  fliplr.cpp
  width.cpp
  logspace.cpp
  pispace.cpp
  freqspace1.cpp
  freqspace2.cpp  
  sum.cpp
  sum2.cpp
  sum1.cpp 
  sump.cpp 
  maximum.cpp
# List of test files for toolbox core.settings
   )

nt2_module_add_tests(core.functions.unit ${SOURCES})
