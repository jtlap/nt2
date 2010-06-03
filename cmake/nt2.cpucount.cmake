################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find Number of cores
################################################################################

IF(UNIX)
execute_process(COMMAND getconf _NPROCESSORS_ONLN 
                OUTPUT_VARIABLE NT2_CONFIG_CPU_COUNT
               )
ENDIF(UNIX)

if(DARWIN)
endif(DARWIN)

if(WINDOWS)
endif(WINDOWS)

