################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(core.sdk)

nt2_module_postconfigure(gather_includes ---ignore details --ignore preprocessed
                                         nt2/core/functions
                                         --out nt2/core/include/functions
                                          nt2/core/include/functions
                                         --out nt2/core/functions.hpp
                                         --out nt2/include/functions
                        )

nt2_module_postconfigure(gather_includes ---ignore details --ignore preprocessed
                                         --max 1 nt2/core/functions
                                         nt2/core/functions/generic nt2/core/functions/scalar
                                         --out nt2/core/include/functions/scalar
                                         nt2/core/include/functions/scalar
                                         --out nt2/include/functions/scalar
                        )

