################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Setup some compliler options
################################################################################
include(CheckCXXCompilerFlag)

################################################################################
# Add pedantic warning level
################################################################################
OPTION(NT2_PEDANTIC "Enable/Disable pedantic warnings" OFF)

IF(NT2_PEDANTIC)
################################################################################
# Check for gcc style
################################################################################
check_cxx_compiler_flag("-pedantic" HAS_GCC_PEDANTIC)
IF(HAS_GCC_PEDANTIC)
set(NT2_FLAGS "${NT2_FLAGS} -pedantic")
set(NT2_PEDANTIC_SET 1)
ENDIF()

################################################################################
# Check for MSVC style
################################################################################
check_cxx_compiler_flag("/W4" HAS_MSVC_PEDANTIC)
IF(HAS_MSVC_PEDANTIC)
set(NT2_FLAGS "${NT2_FLAGS} /W4")
set(NT2_PEDANTIC_SET 1)
ENDIF()

IF(NT2_PEDANTIC_SET)
MESSAGE(STATUS "Enabling pedantic warnings")
ENDIF()
ENDIF()
################################################################################
# Add pedantic warning level done
################################################################################
