################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add global unit driver rules
################################################################################
ADD_CUSTOM_TARGET(core.unit)
ADD_CUSTOM_TARGET(sdk.unit)

################################################################################
# Add all unit directories for core/
################################################################################
#ADD_SUBDIRECTORY(core/time)

################################################################################
# Add all examples directories for sdk/
################################################################################
ADD_SUBDIRECTORY(sdk/meta)
ADD_SUBDIRECTORY(sdk/functor)
ADD_SUBDIRECTORY(sdk/constant)
ADD_SUBDIRECTORY(sdk/memory)
ADD_SUBDIRECTORY(sdk/simd)

################################################################################
# Add driver rule dependencies
################################################################################
ADD_DEPENDENCIES(unit core.unit)  
ADD_DEPENDENCIES(unit sdk.unit)