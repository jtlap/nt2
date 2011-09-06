################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.sdk)

set(SOURCES
    memory/allocate.cpp
    memory/deallocate.cpp
    memory/reallocate.cpp
    config/arm/detect-linux.cpp
    config/arm/get_vendor.cpp
    config/powerpc/detect-linux.cpp
    config/powerpc/detect-macos.cpp
    config/powerpc/get_vendor.cpp
    config/x86/cpuid.cpp
    config/x86/detect.cpp
    config/x86/get_vendor.cpp
    config/hwcap-linux.cpp
   )
nt2_module_add_library(boost_simd ${SOURCES})
