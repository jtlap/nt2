################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(nt2.info)

if(NOT DEFINED NT2_SIMD_FLAGS)

  # x86 Family
  if(NT2_ARCH_X86)
    include(arch/Findx86)
  endif()

  # IBM/Motorola/Apple VMX Family
  if(NT2_ARCH_POWERPC)
    include(arch/FindVMX)
  endif()

endif()

set( NT2_SIMD_FLAGS ${NT2_SIMD_FLAGS}
     CACHE STRING "SIMD extensions compiler flags"
   )
set( NT2_SIMD_EXT ${NT2_SIMD_EXT}
     CACHE STRING "SIMD extension being built for (informative)"
   )
message(STATUS "[boost.simd.sdk] SIMD flag: ${NT2_SIMD_FLAGS}")
