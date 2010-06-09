################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SIMD extensions availability on Intel machines
################################################################################
include(FindMMX)
include(FindSSE2)
include(FindSSSE3)
include(FindSSE3)
include(FindSSE4)
include(FindAVX)

################################################################################
# Check for SIMD extensions availability on PPC machines
################################################################################
#include(FindAltivec)
