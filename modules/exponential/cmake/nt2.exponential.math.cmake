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

check_function_exists(cbrt NT2_TOOLBOX_EXPONENTIAL_HAS_CBRT)
check_function_exists(cbrtf NT2_TOOLBOX_EXPONENTIAL_HAS_CBRTF)

################################################################################
# Generate math.hpp
################################################################################
find_file(NT2_EXPONENTIAL_MATH_HPP math.hpp.cmake ${CMAKE_MODULE_PATH})
configure_file( ${NT2_EXPONENTIAL_MATH_HPP}
                ${PROJECT_BINARY_DIR}/include/nt2/toolbox/exponential/details/math.hpp
              )
