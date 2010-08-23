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

set(VMX_FOUND FALSE)

IF( ${VMX_FOUND} )
MESSAGE( STATUS "PPC Altivec available")
ELSE()
MESSAGE( STATUS "PPC Altivec not available")
ENDIF()

################################################################################
# Advance current test
################################################################################
mark_as_advanced(AVX_FOUND)

