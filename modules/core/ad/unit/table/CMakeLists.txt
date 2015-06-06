##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
# List of table test files for toolbox derivation
   ad_df.cpp
   ad_gradient.cpp
   )

nt2_module_add_tests(core.ad.table.unit ${SOURCES})
