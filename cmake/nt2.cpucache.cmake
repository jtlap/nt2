################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

################################################################################
# Find cache size and cache line size
################################################################################

IF(UNIX)
execute_process(COMMAND getconf LEVEL1_DCACHE_SIZE OUTPUT_VARIABLE NT2_CONFIG_L1_CACHE_SIZE)
execute_process(COMMAND getconf LEVEL1_DCACHE_LINESIZE OUTPUT_VARIABLE NT2_CONFIG_L1_CACHE_LINESIZE)
execute_process(COMMAND getconf LEVEL2_CACHE_SIZE OUTPUT_VARIABLE NT2_CONFIG_L2_CACHE_SIZE)
execute_process(COMMAND getconf LEVEL2_CACHE_LINESIZE OUTPUT_VARIABLE NT2_CONFIG_L2_CACHE_LINESIZE)
execute_process(COMMAND getconf LEVEL3_CACHE_SIZE OUTPUT_VARIABLE NT2_CONFIG_L3_CACHE_SIZE)
execute_process(COMMAND getconf LEVEL3_CACHE_LINESIZE OUTPUT_VARIABLE NT2_CONFIG_L3_CACHE_LINESIZE)
ENDIF(UNIX)

if(DARWIN)
endif(DARWIN)

if(WINDOWS)
endif(WINDOWS)

