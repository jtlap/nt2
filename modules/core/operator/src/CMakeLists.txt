################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(core.operator)
nt2_module_simd_toolbox(operator)

include(nt2.preprocess)
nt2_preprocess(core.operator.preprocess ${NT2_CORE.OPERATOR_ROOT}/include/nt2/core/functions/cons.hpp
               OPTIONS -DNT2_DONT_USE_PREPROCESSED_FILES
                       -DNT2_CREATE_PREPROCESSED_FILES
              )
