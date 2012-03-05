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
#  ind2sub.cpp
   sub2ind.cpp
#  sub2sub.cpp
  size.cpp
  zeros.cpp
  issquare.cpp
  issymetric.cpp
  ishermitian.cpp
  istriangular.cpp
# List of test files for toolbox core.settings
   )

nt2_module_add_tests(core.functions.unit ${SOURCES})
