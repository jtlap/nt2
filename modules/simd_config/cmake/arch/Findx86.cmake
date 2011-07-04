################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(CheckCXXCompilerFlag)

macro(nt2_simd_cpuid_check ext)

  # Check for ext availability
  if(NOT DEFINED BOOST_SIMD_HAS_${ext}_SUPPORT)
    string(TOLOWER ${ext} ext_l)
    string(REPLACE "_" "." ext_l ${ext_l})
    
    find_file(SRC_CPUID src/cpuid.cpp ${CMAKE_MODULE_PATH} NO_DEFAULT_PATH)
    try_run(RUN_RESULT_VAR COMPILE_RESULT_VAR
            ${PROJECT_BINARY_DIR}/cmake
            ${SRC_CPUID}
            CMAKE_FLAGS -DCOMPILE_DEFINITIONS:STRING=${BOOST_SIMD_CURRENT_FLAGS}
            OUTPUT_VARIABLE LOG
            ARGS ${ext_l}
           )

    # If file compiles and run, we're set
    if(COMPILE_RESULT_VAR AND RUN_RESULT_VAR EQUAL 0)
      set(BOOST_SIMD_HAS_${ext}_SUPPORT 1 CACHE INTERNAL "${ext} Support" FORCE)
    else()
      set(BOOST_SIMD_HAS_${ext}_SUPPORT 0 CACHE INTERNAL "${ext} Support" FORCE)
    endif()

    if(BOOST_SIMD_HAS_${ext}_SUPPORT)
      message(STATUS "[boost.simd.config] ${ext} available")

      # Find the proper options
      if(NOT BOOST_SIMD_COMPILER_MSVC)
        check_cxx_compiler_flag("-m${ext_l}" HAS_GCC_${ext})
        if(HAS_GCC_${ext})
	  set(NT2_SIMD_FLAGS "-m${ext_l} ${NT2_SIMD_FLAGS}")
        endif()
      endif()

    else()
      message(STATUS "[boost.simd.config] ${ext} not available")
    endif()
    
  endif()
  
endmacro()

nt2_simd_cpuid_check(AVX)
nt2_simd_cpuid_check(SSE4_2)
nt2_simd_cpuid_check(SSE4_1)
nt2_simd_cpuid_check(SSSE3)
nt2_simd_cpuid_check(SSE3)
nt2_simd_cpuid_check(SSE2)
nt2_simd_cpuid_check(SSE)
nt2_simd_cpuid_check(MMX)

if(BOOST_SIMD_ARCH_AMD)
  nt2_simd_cpuid_check(FMA4)
  nt2_simd_cpuid_check(XOP)
  nt2_simd_cpuid_check(SSE4A)
endif()

################################################################################
# Intel/AMD SSE Family fix-up to force arithmetic to be sse style everywhere
################################################################################

if(BOOST_SIMD_COMPILER_GNU_C)
  foreach(ext avx sse)
    string(TOUPPER ${ext} ext_u)
    
    if(BOOST_SIMD_HAS_${ext_u}_SUPPORT)
      check_cxx_compiler_flag("-mfpmath=${ext}" HAS_GCC_MFPMATH_${ext_u})
      if(HAS_GCC_MFPMATH_${ext_u})
	set(NT2_CXX_PRECISION_FLAGS "-mfpmath=${ext}")
        break()
      endif()
    endif()
    
  endforeach()
endif()

if(BOOST_SIMD_COMPILER_MSVC)
  foreach(ext avx sse2 sse)
    string(TOUPPER ${ext} ext_u)
    
    if(BOOST_SIMD_HAS_${ext_u}_SUPPORT)
      check_cxx_compiler_flag("/arch:${ext_u}" HAS_MSVC_ARCH_${ext_u})
      if(HAS_MSVC_ARCH_${ext_u})
	set(NT2_CXX_PRECISION_FLAGS "/arch:${ext_u}")
        break()
      endif()
    endif()
    
  endforeach()
endif()
