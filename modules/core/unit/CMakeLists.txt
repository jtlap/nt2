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

################################################################################
# Add all unit directories for core/
################################################################################
#ADD_SUBDIRECTORY(core/time)

################################################################################
# Add driver rule dependencies
################################################################################
ADD_DEPENDENCIES(unit core.unit)
