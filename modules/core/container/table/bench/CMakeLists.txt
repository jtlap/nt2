##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

nt2_module_use_modules(unit core.utility)

SET( SOURCES
  small_table.cpp
  redundant_loads.cpp
  plus.cpp
  subscript.cpp
  sum.cpp
#  fluid.cpp
# List of scalar test files for toolbox fuzzy
   )

nt2_module_add_tests(core.container.table.bench ${SOURCES})
