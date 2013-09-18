//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_GENERATOR_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/dsl/typed_expression.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    struct mpl_2
    {
      template<class X, class Y>
      struct apply
      {
        typedef Y type;
      };
    };
  }

  struct generator
    : proto::transform<generator>
  {
    template<class Expr, class State, class Data>
    struct impl : proto::transform_impl<Expr, State, Data>
    {
        typedef typename boost::remove_const<typename impl::expr>::type raw_expr;

        typedef typename mpl::apply1< meta::typed_expression<details::mpl_2>, raw_expr>::type semantic;
        typedef expression<raw_expr, semantic> simd_expr;

        typedef typename mpl::if_< dispatch::meta::is_scalar<semantic>, semantic, simd_expr >::type result_type;

        BOOST_FORCEINLINE
        result_type
        operator()( typename impl::expr_param e
                  , typename impl::state_param
                  , typename impl::data_param
                  ) const
        {
          simd_expr const that = {e};
          return that;
        }
    };
  };
} }

#endif
