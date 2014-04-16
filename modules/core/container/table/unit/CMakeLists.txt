##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################
nt2_module_use_modules(test.unit)

include(nt2.pch)
nt2_pch(nt2/table.hpp)

SET( SOURCES
  as_size.cpp
  composite_table.cpp
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
  sx.cpp
  sxfun.cpp
  table_returning.cpp
  table_settings.cpp
  tie.cpp
  transform.cpp
  width.cpp
# List of scalar test files for toolbox core.container.table
   )

nt2_module_add_tests(core.container.table.unit ${SOURCES})
