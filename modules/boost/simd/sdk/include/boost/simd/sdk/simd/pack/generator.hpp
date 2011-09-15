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
#include <boost/proto/select.hpp>
#include <boost/proto/traits.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    struct generator_cases
    {
      template<int N>
      struct case_c_;
        
      template<class N>
      struct case_ : case_c_<N::value> {};
    };
    
    #define M0(z, n, t)                                                        \
    template<>                                                                 \
    struct generator_cases::case_c_<n>                                         \
     : proto::transform<generator_cases::case_c_<n> >                          \
    {                                                                          \
      template<class Expr, class State, class Data>                            \
      struct impl : proto::transform_impl<Expr, State, Data>                   \
      {                                                                        \
        typedef expression< typename impl::expr                                \
                          , typename dispatch::meta::                          \
                            call< typename proto::                             \
                                  tag_of<typename impl::expr>::type            \
                                  (                                            \
                                    BOOST_PP_ENUM(n, M1, ~)                    \
                                  )                                            \
                                >::type                                        \
                          > result_type;                                       \
                                                                               \
        BOOST_DISPATCH_FORCE_INLINE                                            \
        result_type                                                            \
        operator()( typename impl::expr_param e                                \
                  , typename impl::state_param s                               \
                  , typename impl::data_param d                                \
                  ) const                                                      \
        {                                                                      \
          result_type const that = {e};                                        \
          return that;                                                         \
        }                                                                      \
      };                                                                       \
    };                                                                         \
    /**/
    
    #define M1(z, n, t)                                                        \
    typename dispatch::meta::                                                  \
    semantic_of< typename proto::result_of::                                   \
                 child_c<typename impl::expr, n>::type                         \
               >::type                                                         \
    /**/
    
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_ARITY, M0, ~)
    
    #undef M1
    #undef M0
    
    // terminal case
    template<>
    struct generator_cases::case_c_<0>
     : proto::transform<generator_cases::case_c_<0> >
    {
      template<class Expr, class State, class Data>
      struct impl : proto::transform_impl<Expr, State, Data>
      {
        typedef expression< typename impl::expr
                          , typename dispatch::meta::
                            call< typename proto::
                                  tag_of<typename impl::expr>::type
                                  (
                                    typename proto::result_of::
                                    value<typename impl::expr>::type
                                  )
                                >::type
                          > result_type;

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
  }
  
  struct generator
    : proto::select_< details::generator_cases, proto::arity_of<proto::_>() >
  {
  };
} }

#endif
