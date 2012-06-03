##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  all.cpp
  any.cpp
  arecatcompatible.cpp
  asum1.cpp
  asum2.cpp
  asump.cpp
  band.cpp
  blkdiag.cpp
  cat.cpp
  cic.cpp
  cif.cpp
  class.cpp
  colon.cpp
  cols.cpp
  colvect.cpp
  diag_of.cpp
  dot.cpp
  expand.cpp
  eye.cpp
  first_last_index.cpp
  firstnonsingleton.cpp
  flipdim.cpp
  fliplr.cpp
  flipud.cpp
  freqspace.cpp
  freqspace1.cpp
  freqspace2.cpp
  from_diag.cpp
  havesamesize.cpp
  horzcat.cpp
  ind2sub.cpp
  iscolumn.cpp
  isempty.cpp
  isequal.cpp
  isequaln.cpp
  isfloating.cpp
  ishermitian.cpp
  isinside.cpp
  isinteger.cpp
  ismatrix.cpp
  isrow.cpp
  isscalar.cpp
  issquare.cpp
  issymetric.cpp
  istriangular.cpp
  istril.cpp
  istriu.cpp
  isvector.cpp
  isvectoralong.cpp
  length.cpp
  linspace.cpp
  logspace.cpp
  maximum.cpp
  mean.cpp
  minimum.cpp
  inbtrue.cpp
  nbtrue.cpp
  ndims.cpp
  none.cpp
  norm2.cpp
  normp.cpp
  numel.cpp
  ones.cpp
  pispace.cpp
  prod.cpp
  relative_index.cpp
  relative_size.cpp
  repnum.cpp
  reshape.cpp
  resize.cpp
  ric.cpp
  rif.cpp
  rows.cpp
  rowvect.cpp
  size.cpp
  squeeze.cpp
  streaming.cpp
  sub2ind.cpp
  sub2sub.cpp
  subscript.cpp
  sum.cpp
  tie.cpp
  tri1l.cpp
  tri1u.cpp
  tril.cpp
  triu.cpp
  vertcat.cpp
  width.cpp
  zeros.cpp
  cast.cpp
  bsxfun.cpp
  wmean.cpp
#  fill_pattern.cpp
#  repmat.cpp
#  rephorz.cpp
#  repvert.cpp
#  nansum.cpp
#  nanmean.cpp
#  nanasum2.cpp
# List of test files for toolbox core.settings
   )
set(CMAKE_CXX_FLAGS_NT2TEST "${CMAKE_CXX_FLAGS_NT2TEST} -Wfatal-errors")
nt2_module_add_tests(core.functions.unit ${SOURCES})
