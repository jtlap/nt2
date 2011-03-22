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

check_function_exists(y0 NT2_TOOLBOX_BESSEL_HAS_Y0)
check_function_exists(y0f NT2_TOOLBOX_BESSEL_HAS_Y0F)
check_function_exists(_y0 NT2_TOOLBOX_BESSEL_HAS__Y0)
check_function_exists(_y0f NT2_TOOLBOX_BESSEL_HAS__Y0F)

check_function_exists(y1 NT2_TOOLBOX_BESSEL_HAS_Y1)
check_function_exists(y1f NT2_TOOLBOX_BESSEL_HAS_Y1F)
check_function_exists(_y1 NT2_TOOLBOX_BESSEL_HAS__Y1)
check_function_exists(_y1f NT2_TOOLBOX_BESSEL_HAS__Y1F)

check_function_exists(yn NT2_TOOLBOX_BESSEL_HAS_YN)
check_function_exists(ynf NT2_TOOLBOX_BESSEL_HAS_YNF)
check_function_exists(_yn NT2_TOOLBOX_BESSEL_HAS__YN)
check_function_exists(_ynf NT2_TOOLBOX_BESSEL_HAS__YNF)

################################################################################
# Generate math.hpp
################################################################################
find_file(NT2_BESSEL_MATH_HPP math.hpp.cmake ${CMAKE_MODULE_PATH})
configure_file( ${NT2_BESSEL_MATH_HPP}
                ${PROJECT_BINARY_DIR}/include/nt2/toolbox/bessel/details/math.hpp
              )
