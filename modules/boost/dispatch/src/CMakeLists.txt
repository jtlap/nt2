################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(boost.dispatch)

include(nt2.preprocess)
nt2_preprocess(boost.dispatch.preprocess ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/dsl/unpack.hpp
               OPTIONS -DBOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES
                       -DBOOST_DISPATCH_CREATE_PREPROCESSED_FILES
              )
