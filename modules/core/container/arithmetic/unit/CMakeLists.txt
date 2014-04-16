##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################
nt2_module_use_modules(test.unit core.container.table)

include(nt2.pch)
nt2_pch(nt2/table.hpp)

SET ( SOURCES
      center.cpp
      linear_interp.cpp
      remquo.cpp
      two_add.cpp
      two_prod.cpp
      two_split.cpp
# List of table test files for toolbox predicates
    )

nt2_module_add_tests(core.container.arithmetic.unit ${SOURCES})
