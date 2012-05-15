//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_TIE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_TIE_HPP_INCLUDED

#include <nt2/core/functions/tie.hpp>
#include <nt2/core/container/dsl/domain.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace nt2 { namespace ext
{

#define M0(z,n,t) boost::ref(boost::proto::as_child(a##n))
#define M1(z,n,t) (A##n)
#define M2(z,n,t) (unspecified_<A##n>) // FIXME: ambiguous with generic_ / common
#define M3(z,n,t) typename boost::proto::result_of::as_child<A##n>::type&

#define M4(z,n,t)                                                                 \
NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tie_, tag::cpu_                             \
                          , BOOST_PP_REPEAT(n,M1,~)                               \
                          , BOOST_PP_REPEAT(n,M2,~)                               \
                          )                                                       \
{                                                                                 \
  typedef typename  boost::proto::result_of::make_expr                            \
                    < nt2::tag::tie_, container::domain                           \
                    , BOOST_PP_ENUM(n,M3,~)                                       \
                    >::type                       result_type;                    \
                                                                                  \
  BOOST_FORCEINLINE result_type                                                   \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,A,& a)) const                          \
  {                                                                               \
    return  boost::proto::                                                        \
            make_expr<nt2::tag::tie_, container::domain>(BOOST_PP_ENUM(n,M0,~));  \
  }                                                                               \
};                                                                                \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_DISPATCH_MAX_META_ARITY,M4,~)

#undef M0
#undef M1
#undef M2
#undef M3
#undef M4
} }

#endif
