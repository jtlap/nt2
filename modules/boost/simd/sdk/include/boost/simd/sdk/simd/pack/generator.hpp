/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/proto/traits.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace simd
{

namespace meta
{
  template<class Lambda>
  struct lambda_pod_generator
    : proto::transform< lambda_pod_generator<Lambda> >
  {
    template<class Expr, class State, class Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef typename mpl::apply1<Lambda, typename impl::expr>::type result_type;
        
        BOOST_DISPATCH_FORCE_INLINE
        result_type
        operator()( typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                  ) const
        {
          result_type const that = {e};
          return that;
        }
    };
  };
  
  template<class Lambda>
  struct expression_type
  {
    template<class Expr, int N>
    struct apply_impl;
      
    template<class Expr>
    struct apply
      : apply_impl<Expr, proto::arity_of<Expr>::value>
    {
    };
    
    #define M0(z, n, t)                                                        \
    template<class Expr>                                                       \
    struct apply_impl<Expr, n>                                                 \
     : mpl::apply2< Lambda                                                     \
                  , Expr                                                       \
                  , typename dispatch::meta::                                  \
                    call< typename proto::                                     \
                          tag_of<Expr>::type                                   \
                          (                                                    \
                            BOOST_PP_ENUM(n, M1, ~)                            \
                          )                                                    \
                        >::type                                                \
                  >                                                            \
    {                                                                          \
    };                                                                         \
    /**/
    
    #define M1(z, n, t)                                                        \
    typename dispatch::meta::                                                  \
    semantic_of< typename proto::result_of::                                   \
                 child_c<Expr, n>::type                                        \
               >::type                                                         \
    /**/
    
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
    
    #undef M1
    #undef M0
    
    // terminal case
    template<class Expr>
    struct apply_impl<Expr, 0>
     : mpl::apply2< Lambda
                  , Expr
                  , typename dispatch::meta::
                    call< typename proto::
                          tag_of<Expr>::type
                          (
                            typename proto::result_of::
                            value<Expr>::type
                          )
                        >::type
                  >
    {
    };
  };
}

  typedef meta::
          lambda_pod_generator< meta::
                                expression_type< typename mpl::
                                                 lambda< expression<mpl::_1, mpl::_2> >::type
                                               >
                              > generator;
} }

#endif
