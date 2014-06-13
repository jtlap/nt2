##############################################################################
###   Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
###   Copyright 2012 - 2014 NumScale SAS
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

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
