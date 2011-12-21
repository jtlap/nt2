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
nt2_preprocess(boost.dispatch0x.preprocess ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/functor/functor.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/functor/details/dispatch.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/functor/meta/call.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/dsl/call.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/type_traits/common_type.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/meta/floating.hpp
                                           ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/meta/result_of.hpp
               OPTIONS -DBOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES
                       -DBOOST_DISPATCH_CREATE_PREPROCESSED_FILES
              )
              
nt2_preprocess(boost.dispatch03.preprocess ${NT2_BOOST.DISPATCH_ROOT}/include/boost/dispatch/functor/functor.hpp
               OPTIONS -DBOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES
                       -DBOOST_DISPATCH_CREATE_PREPROCESSED_FILES
                       -DBOOST_DISPATCH_CREATE_PREPROCESSED_FILES_NO_0X
              )
            
if(NT2_PREPROCESS_ENABLED)
  add_custom_target(boost.dispatch.preprocess)
  add_dependencies(boost.dispatch.preprocess boost.dispatch0x.preprocess boost.dispatch03.preprocess)
endif()
