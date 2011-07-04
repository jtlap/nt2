################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(simd_operator)
#nt2_module_configure_toolbox(operator 1)

nt2_module_configure_include(boost/simd/toolbox/operator/function -o boost/simd/toolbox/operator/include -o boost/simd/include/functions)
nt2_module_configure_simd(boost/simd/toolbox/operator/function)

include(nt2.preprocess)
nt2_preprocess(simd_operator.preprocess ${NT2_OPERATOR_ROOT}/include/nt2/toolbox/operator/specific/common.hpp
                                   ${NT2_OPERATOR_ROOT}/include/nt2/toolbox/operator/function/simd/common/map.hpp
                                   ${NT2_OPERATOR_ROOT}/include/nt2/toolbox/operator/function/simd/sse/sse2/map.hpp
              )
