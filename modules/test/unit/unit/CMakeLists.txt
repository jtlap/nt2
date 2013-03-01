################################################################################
#         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#         Copyright 2012        MetaScale SAS
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http:#www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# This is a very simple bootstrap test for unit test themselves
################################################################################

SET( SOURCES
     is_equal.cpp
     max_ulp.cpp
     pass_fail.cpp
   )

nt2_module_add_tests(test.unit.unit ${SOURCES})
