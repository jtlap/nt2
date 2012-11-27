################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.simd.sdk)

nt2_module_postconfigure(gather_includes ---ignore details --ignore preprocessed
                                         boost/simd/dsl/functions
                                         --out  boost/simd/dsl/include/functions
                                          boost/simd/dsl/include/functions
                                         --out  boost/simd/dsl/functions.hpp
                                         --out  boost/simd/include/functions
                        )

nt2_module_postconfigure(gather_includes --max 1 boost/simd/sdk/simd/extensions
                                         --out boost/simd/sdk/simd/extensions/extensions.hpp
                        )
