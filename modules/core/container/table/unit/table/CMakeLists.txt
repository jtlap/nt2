##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  as_size.cpp
  composite_table.cpp
  cons.cpp
  constructor.cpp
  disp.cpp
  erase.cpp
  find.cpp
  findi.cpp
  findj.cpp
  first_last_index.cpp
  firstnonsingleton.cpp
  firstoflength.cpp
  globalfind.cpp
  histc.cpp
  length.cpp
  linesstride.cpp
  multind.cpp
  nblines.cpp
  ndims.cpp
  push_back.cpp
  relative_index.cpp
  relative_size.cpp
  resize.cpp
  size.cpp
  subscript.cpp
  swap.cpp
  sx.cpp
  sxfun.cpp
  table_returning.cpp
  table_settings.cpp
  tie.cpp
  transform.cpp
  width.cpp
  is_vector.cpp
# List of scalar test files for toolbox core.container.table
   )

nt2_module_add_tests(core.container.table.unit ${SOURCES})
