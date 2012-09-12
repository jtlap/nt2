################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

# signal only works on x86 for now
include(nt2.info)
if(NOT NT2_ARCH_X86)
  set(NT2_SIGNAL_DEPENDENCIES_FOUND 0)
endif()

SET(NT2_SIGNAL_DEPENDENCIES_EXTRA sdk.simd operator constant arithmetic bitwise trigonometric exponential)
