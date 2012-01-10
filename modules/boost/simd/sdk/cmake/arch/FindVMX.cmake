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

# On UNIX, we grep the /proc/cpuinfo entry
if(NT2_OS_UNIX)
  find_file(ALTIVEC_SH arch/altivec.sh ${CMAKE_MODULE_PATH})
  execute_process( COMMAND ${ALTIVEC_SH}
                   OUTPUT_VARIABLE NT2_HAS_VMX_SUPPORT
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                 )
endif()

# On OS X, we use systcl
if(NT2_OS_MAC_OS)
  execute_process( COMMAND sysctl -n hw.optional.altivec
                   OUTPUT_VARIABLE NT2_HAS_VMX_SUPPORT
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                 )
endif()
  
if(NT2_HAS_VMX_SUPPORT)
  message(STATUS "[boost.simd.sdk] PPC Altivec available")
  set(NT2_SIMD_EXT altivec CACHE STRING "SIMD extension being built for (informative)")
    
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
