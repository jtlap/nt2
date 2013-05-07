################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.constant)
nt2_module_configure_toolbox(constant 1)

nt2_module_postconfigure(gather_includes ---ignore details --ignore preprocessed
                                         boost/simd/sdk/constant/impl
                                         --out boost/simd/sdk/constant
                        )
