################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Add all examples directories for core/
################################################################################
ADD_SUBDIRECTORY(core/timing)

################################################################################
# Add all examples directories for sdk/
################################################################################
ADD_SUBDIRECTORY(sdk/config)
ADD_SUBDIRECTORY(sdk/details)
#ADD_SUBDIRECTORY(sdk/errors)
ADD_SUBDIRECTORY(sdk/meta)
ADD_SUBDIRECTORY(sdk/functor)
#ADD_SUBDIRECTORY(sdk/memory)
#ADD_SUBDIRECTORY(sdk/constants)
#ADD_SUBDIRECTORY(sdk/simd)

