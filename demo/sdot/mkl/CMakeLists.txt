################################################################################
#         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
#         Copyright 2012 - 2013 MetaScale SAS
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
cmake_minimum_required(VERSION 2.8)

set(NT2_DIR ${CMAKE_SOURCE_DIR}/../../../cmake)

set(NT2_BLAS_MULTICORE 0)

find_package(NT2 REQUIRED)
include(${NT2_USE_FILE})

set(CMAKE_BUILD_TYPE Release)
if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-DBOOST_SIMD_NO_STRICT_ALIASING -fno-strict-aliasing)
endif()

add_executable(sdot_mkl sdot_mkl.cpp)

#The MKLROOT environment variable must be set by the user. This can be done by running the script compilervars.sh in the bin folder of your mkl installation.
#The linker command below may need to be modified for your paticular mkl installation. Use the mkl link advisor http://software.intel.com/sites/products/mkl/MKL_Link_Line_Advisor.html to generate the correct link command for your system and paste it below.

target_link_libs(sdot_mkl -Wl,--start-group  ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_sequential.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm)
