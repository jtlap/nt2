//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/include/functions/aggregate.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
#define M0(z,n,t) (I##n)
#define M1(z,n,t) (unspecified_<I##n>)

#define M2(z,n,t)                                                             \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::function_, tag::cpu_                    \
                          , (A0)BOOST_PP_REPEAT(n,M0,~)                       \
                          , (ast_<A0>)BOOST_PP_REPEAT(n,M1,~)                 \
                          )                                                   \
{                                                                             \
  typedef typename                                                            \
  meta::call< tag::aggregate_                                                 \
              (                                                               \
                BOOST_PP_ENUM_BINARY_PARAMS(n,I,& BOOST_PP_INTERCEPT)         \
              )                                                               \
            >::type                                             indices;      \
  typedef typename nt2::make_size<n>::type                      size_type;    \
                                                                              \
  typedef typename  boost::proto::result_of::                                 \
                    make_expr < nt2::tag::function_                           \
                              , container::domain                             \
                              , A0&                                           \
                              , indices                                       \
                              , box<size_type>                                \
                              >::type                           result_type;  \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(A0& a0, BOOST_PP_ENUM_BINARY_PARAMS(n,const I,& i) ) const       \
  {                                                                           \
    size_type compact(a0.extent());                                           \
    return boost::proto::make_expr<tag::function_,container::domain>          \
                                  ( boost::reference_wrapper<A0>(a0)          \
                                  , nt2::aggregate(BOOST_PP_ENUM_PARAMS(n,i)) \
                                  , nt2::boxify(compact)                      \
                                  );                                          \
  }                                                                           \
};                                                                            \
/**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M2,~)

#undef M0
#undef M1
#undef M2
} }

#endif
