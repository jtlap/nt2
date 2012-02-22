################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.operator)
nt2_module_configure_toolbox(operator 1)

include(nt2.preprocess)
nt2_preprocess(boost.simd.operator.preprocess ${NT2_BOOST.SIMD.OPERATOR_ROOT}/include/boost/simd/toolbox/operator/specific/common.hpp
                                              ${NT2_BOOST.SIMD.OPERATOR_ROOT}/include/boost/simd/toolbox/operator/functions/simd/common/map.hpp
                                              ${NT2_BOOST.SIMD.OPERATOR_ROOT}/include/boost/simd/toolbox/operator/functions/simd/sse/sse2/map.hpp
                                              ${NT2_BOOST.SIMD.OPERATOR_ROOT}/include/boost/simd/toolbox/operator/functions/simd/sse/avx/map.hpp
               OPTIONS -DBOOST_SIMD_DONT_USE_PREPROCESSED_FILES
                       -DBOOST_SIMD_CREATE_PREPROCESSED_FILES
                       -DBOOST_SIMD_HAS_AVX_SUPPORT
              )
