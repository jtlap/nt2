##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  composite_table.cpp
  table_settings.cpp
  resize.cpp
  constructor.cpp
  table_returning.cpp
  multind.cpp
  composite_table.cpp
# List of scalar test files for toolbox core.settings
   )

nt2_module_add_tests(core.container.table.unit ${SOURCES})
