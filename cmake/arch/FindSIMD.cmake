################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for SIMD extensions availability
################################################################################
include(arch/FindMMX)
include(arch/FindSSE2)
include(arch/FindSSE3)
include(arch/FindSSSE3)
include(arch/FindSSE4)
include(arch/FindAVX)
include(arch/FindXOP)
include(arch/FindFMA4)
include(arch/FindVMX)
