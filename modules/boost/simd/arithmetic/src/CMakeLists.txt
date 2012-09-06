################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.arithmetic)
nt2_module_configure_toolbox(arithmetic 1)

################################################################################
# Find out which C99/TR1 math functions are available
################################################################################

include(CheckFunctionExists)

if(UNIX)
  set(CMAKE_REQUIRED_LIBRARIES m)
endif()

check_function_exists(remquo BOOST_SIMD_TOOLBOX_ARITHMETIC_HAS_REMQUO)

################################################################################
# Generate math.hpp
################################################################################
nt2_module_configure_file(math.hpp.cmake
                          boost/simd/toolbox/arithmetic/details/math.hpp
                         )
