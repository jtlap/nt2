##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  backward.cpp
  d2f.cpp
  forward.cpp
  centered.cpp
  vand.cpp
# List of scalar test files for toolbox derivation
   )

nt2_module_add_tests(core.derivation.scalar.unit ${SOURCES})
