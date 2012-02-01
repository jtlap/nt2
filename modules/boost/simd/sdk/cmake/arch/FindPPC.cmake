################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Check for Altivec VMX availability
################################################################################

nt2_module_tool(is_supported vmx RESULT_VARIABLE RESULT_VAR OUTPUT_QUIET)
if(RUN_RESULT_VAR EQUAL 0)
  set(NT2_HAS_VMX_SUPPORT 1)
else()
  set(NT2_HAS_VMX_SUPPORT 0)
endif()

if(NT2_HAS_VMX_SUPPORT)
  message(STATUS "[boost.simd.sdk] PPC Altivec available")
  set(NT2_SIMD_EXT altivec)

  # Find the proper options to compile
  check_cxx_compiler_flag("-maltivec" HAS_GCC_VMX)

  if(HAS_GCC_VMX)
    set(NT2_SIMD_FLAGS "-maltivec -Uvector")
  else()
    set(NT2_SIMD_FLAGS "-DBOOST_SIMD_HAS_VMX_SUPPORT")
  endif()

else()
  message(STATUS "[boost.simd.sdk] PPC Altivec not available")
  set(NT2_SIMD_FLAGS " ")
endif()
