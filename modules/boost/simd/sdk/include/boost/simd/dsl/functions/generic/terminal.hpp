//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_TERMINAL_HPP_INCLUDED

#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/meta/identity.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_REGISTER_DISPATCH_TO( boost::simd::tag::terminal_, tag::formal_
                            , (A0)
                            , (ast_<A0>)
                            , identity
                            )
    
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::terminal_,tag::cpu_
                            , (A0)
                            , (ast_<A0>)
                            )
  {
    template<class Sig>
    struct result;
    
    template<class This, class A0_>
    struct result<This(A0_)>
      : proto::result_of::value<A0_>
    {
    };
    
    template<class A0_>
    typename result<implement(A0_&)>::type
    operator()(A0_& a0) const
    {
      return boost::proto::value(a0);
    }
  };
} } }

#endif
