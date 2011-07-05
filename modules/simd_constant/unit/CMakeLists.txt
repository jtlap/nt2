################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add global unit driver rules
################################################################################
ADD_CUSTOM_TARGET(simd_constant.scalar.unit)
ADD_CUSTOM_TARGET(simd_constant.simd.unit)
ADD_DEPENDENCIES(simd_constant.unit simd_constant.scalar.unit simd_constant.simd.unit)

nt2_module_use_modules(simd_unit simd_operator)
ADD_SUBDIRECTORY(scalar)
ADD_SUBDIRECTORY(simd)
