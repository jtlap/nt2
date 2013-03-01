##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  arecatcompatible.cpp
  arecrosscompatible.cpp
  as_index.cpp
  as_size.cpp
  as_subscript.cpp
  bsxfun.cpp
  class.cpp
  disp.cpp
  find.cpp
  findi.cpp
  findj.cpp
  globalfind.cpp
  first_last_index.cpp
  firstnonsingleton.cpp
  firstoflength.cpp
  havesamesize.cpp
  length.cpp
  linesstride.cpp
  max_extent.cpp
  nblines.cpp
  ndims.cpp
  numel.cpp
  ofsameheight.cpp
  ofsamewidth.cpp
  of_size.cpp
  of_size_max.cpp
  relative_index.cpp
  relative_size.cpp
  size.cpp
  sx.cpp
  tie.cpp
  tsxfun.cpp
  whereij.cpp
  width.cpp
# List of test files for toolbox core.utility
   )

nt2_module_add_tests(core.utility.functions.unit ${SOURCES})
