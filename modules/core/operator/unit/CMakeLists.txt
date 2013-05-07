################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

nt2_module_use_modules( test.unit core.bitwise
                        core.container.table core.container.placeholders
                      )

ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
ADD_SUBDIRECTORY(table)
