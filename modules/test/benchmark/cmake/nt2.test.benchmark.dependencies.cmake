################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################
SET ( NT2_TEST.BENCHMARK_DEPENDENCIES_EXTRA test.unit
                                            boost.dispatch
                                            sdk.config
                                            sdk.error
                                            sdk.timing
    )

SET ( NT2_TEST.BENCHMARK_LIBRARIES optimized nt2_bench debug nt2_bench_d)
