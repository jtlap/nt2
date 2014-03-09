################################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

nt2_module_use_modules(test.unit core.container.table)

include(nt2.pch)
nt2_pch(nt2/table.hpp)

ADD_SUBDIRECTORY(arithmetic)
ADD_SUBDIRECTORY(bitwise)
ADD_SUBDIRECTORY(boolean)
ADD_SUBDIRECTORY(constant)
ADD_SUBDIRECTORY(utility)
ADD_SUBDIRECTORY(ieee)
ADD_SUBDIRECTORY(operator)
ADD_SUBDIRECTORY(predicates)
