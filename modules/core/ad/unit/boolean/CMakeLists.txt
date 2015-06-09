##############################################################################
###          Copyright 2015 J.T. Lapreste
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES

# List of scalar test files for toolbox ad
   if_allbits_else.cpp
   if_else_allbits.cpp
   if_else_zero.cpp
   ifnotadd.cpp
   ifnotdec.cpp
   ifnotinc.cpp
   ifnotsub.cpp
   if_one_else_zero.cpp
   if_zero_else.cpp
   if_zero_else_one.cpp
   negif.cpp
   negifnot.cpp
   seladd.cpp
   seldec.cpp
   selinc.cpp
   selsub.cpp
   )

nt2_module_add_tests(core.ad.boolean.unit ${SOURCES})
