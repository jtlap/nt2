//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_PACK_TERMINAL_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_PACK_TERMINAL_HPP_INCLUDED

#include <boost/simd/dsl/functions/terminal.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( tag::terminal_,tag::cpu_
                                , (class Value)(class State)
                                  (class Data)(std::size_t N)
                                , ((array_<scalar_< arithmetic_<Value > >,N>))
                                  ((target_<array_<scalar_< arithmetic_<State> >,N> >))
                                  (scalar_< integer_<Data> >)
                                )
{
    typedef typename Value::value_type result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type
    operator()( Value const& v, State const&, Data const& p ) const
    {
      return v[p];
    }
  };
} } }

#endif
