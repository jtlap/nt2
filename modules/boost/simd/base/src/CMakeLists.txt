################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.base)
nt2_module_configure_toolbox(arithmetic 1)
nt2_module_configure_toolbox(bitwise 1)
nt2_module_configure_toolbox(boolean 1)
nt2_module_configure_toolbox(ieee 1)
nt2_module_configure_toolbox(operator 1)
nt2_module_configure_toolbox(predicates 1)

include(nt2.preprocess)
nt2_preprocess(boost.simd.base.preprocess ${NT2_BOOST.SIMD.BASE_ROOT}/include/boost/simd/operator/functions/simd/common/map.hpp
                                          ${NT2_BOOST.SIMD.BASE_ROOT}/include/boost/simd/operator/functions/simd/sse/sse2/map.hpp
                                          ${NT2_BOOST.SIMD.BASE_ROOT}/include/boost/simd/operator/functions/simd/sse/avx/map.hpp
                                          ${NT2_BOOST.SIMD.BASE_ROOT}/include/boost/simd/operator/specific/common.hpp
               OPTIONS -DBOOST_SIMD_DONT_USE_PREPROCESSED_FILES
                       -DBOOST_SIMD_CREATE_PREPROCESSED_FILES
                       -DBOOST_SIMD_HAS_SSE2_SUPPORT
                       -DBOOST_SIMD_HAS_AVX_SUPPORT
               DEPENDS boost.dispatch.preprocess
              )
