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
# Add Extra warning level
################################################################################
OPTION(NT2_EXTRA_WARNINGS "Enable/Disable extra warnings" OFF)

IF(NT2_EXTRA_WARNINGS)
################################################################################
# Check for gcc style
################################################################################
check_cxx_compiler_flag("-Wextra" HAS_GCC_WEXTRA)
IF(HAS_GCC_WEXTRA)
set(NT2_FLAGS "${NT2_FLAGS} -Wall -Wextra -pedantic -ansi")
set(NT2_EXTRA_WARNINGS_SET 1)
ENDIF()

################################################################################
# Check for MSVC style
################################################################################
check_cxx_compiler_flag("/W4" HAS_MSVC_WEXTRA)
IF(HAS_MSVC_WEXTRA)
set(NT2_FLAGS "${NT2_FLAGS} /W4")
set(NT2_EXTRA_WARNINGS_SET 1)
ENDIF()

IF(NT2_EXTRA_WARNINGS_SET)
MESSAGE(STATUS "Enabling extra warnings")
ENDIF()
ENDIF()
################################################################################
# Add Extra warning level done
################################################################################
