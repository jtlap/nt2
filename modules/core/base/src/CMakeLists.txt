################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(core.base)
nt2_module_simd_toolbox(arithmetic base)
nt2_module_simd_toolbox(bitwise base)
nt2_module_simd_toolbox(boolean base)
nt2_module_simd_toolbox(ieee base)
nt2_module_simd_toolbox(operator base)
nt2_module_simd_toolbox(predicates base)
nt2_module_simd_toolbox(constant base)

include(nt2.preprocess)
nt2_preprocess( core.base.operator.preprocess
                ${NT2_CORE.BASE_ROOT}/include/nt2/core/functions/cons.hpp
                OPTIONS -DNT2_DONT_USE_PREPROCESSED_FILES
                        -DNT2_CREATE_PREPROCESSED_FILES
                DEPENDS boost.simd.base.preprocess
              )
