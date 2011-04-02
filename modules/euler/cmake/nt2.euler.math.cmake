##########################################]#####################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find out which C99/TR1 math functions are available
################################################################################

include(CheckFunctionExists)

if(UNIX)
  set(CMAKE_REQUIRED_LIBRARIES m)
endif()

check_function_exists(tgamma NT2_TOOLBOX_EULER_HAS_TGAMMA)
check_function_exists(tgammaf NT2_TOOLBOX_EULER_HAS_TGAMMAF)

check_function_exists(lgamma NT2_TOOLBOX_EULER_HAS_LGAMMA)
check_function_exists(lgammaf NT2_TOOLBOX_EULER_HAS_LGAMMAF)

################################################################################
# Generate math.hpp
################################################################################
find_file(NT2_EULER_MATH_HPP math.hpp.cmake ${CMAKE_MODULE_PATH})
configure_file( ${NT2_EULER_MATH_HPP}
                ${PROJECT_BINARY_DIR}/include/nt2/toolbox/euler/details/math.hpp
              )
