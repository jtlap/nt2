################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

include(NT2Module)
nt2_module_source_setup(dispatch)

include(nt2.preprocess)
nt2_preprocess(dispatch0x.preprocess ${NT2_DISPATCH_ROOT}/include/boost/dispatch/functor/functor.hpp
                                     ${NT2_DISPATCH_ROOT}/include/boost/dispatch/functor/details/dispatch.hpp
                                     ${NT2_DISPATCH_ROOT}/include/boost/dispatch/functor/meta/call.hpp
#                                    ${NT2_DISPATCH_ROOT}/include/boost/dispatch/dsl/call.hpp
                                     ${NT2_DISPATCH_ROOT}/include/boost/dispatch/meta/arithmetic.hpp
                                     ${NT2_DISPATCH_ROOT}/include/boost/dispatch/meta/floating.hpp
                                     ${NT2_DISPATCH_ROOT}/include/boost/dispatch/meta/result_of.hpp
              )
              
nt2_preprocess(dispatch03.preprocess ${NT2_DISPATCH_ROOT}/include/boost/dispatch/functor/functor.hpp
               OPTIONS -DBOOST_DISPATCH_CREATE_PREPROCESSED_FILES_NO_0X
              )
              
add_custom_target(dispatch.preprocess DEPENDS dispatch0x.preprocess dispatch03.preprocess)
