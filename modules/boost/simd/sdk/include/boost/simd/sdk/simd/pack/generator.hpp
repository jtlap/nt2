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
#include <boost/proto/select.hpp>
#include <boost/proto/traits.hpp>

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
    {                                                                          \
      template<class Sig>                                                      \
      struct result;                                                           \
                                                                               \
      template<class This, class Expr>                                         \
      struct result<This(Expr)>                                                \
      {                                                                        \
        typedef expression< Expr                                               \
                          , typename dispatch::meta:                           \
                                     call< typename proto::tag_of<Expr>::type  \
                                           (                                   \
                                             BOOST_PP_ENUM(n, M1, ~)           \
                                           )                                   \
                                         >::type                               \
                          > type;                                              \
      };                                                                       \
    };
    
    #define M1(z, n, t) typename proto::result_of::child_c<Expr, n>::type::result_type
    
    BOOST_PP_REPEAT(BOOST_DISPATCH_MAX_ARITY, M0, ~)
    
    #undef M1
    #undef M0
  }
  
  struct generator
    : proto::select_< generator_cases, proto::arity_of<proto::_>() >
  {
  };
} }

#endif
