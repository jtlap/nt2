/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_CALL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_CALL_HPP_INCLUDED

#include <boost/simd/sdk/dsl/literal.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register terminal handlers for SIMD expression - native case
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::terminal_,tag::cpu_
                            , (Value)(State)(Data)(X)
                            , ((simd_<arithmetic_<Value>,X>))
                              ((target_<simd_<arithmetic_<State>,X> >))
                              (scalar_< integer_<Data> >)
                            )
  {
    typedef Value result_type;

    inline result_type
    operator()( Value const& v, State const& , Data const& ) const
    {
      return v;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_TPL( tag::terminal_,tag::cpu_
                                , (class Value)(class State)
                                  (class Data)(std::size_t N)
                                , ((array_<scalar_< arithmetic_<Value > >,N>))
                                  ((target_<array_<scalar_< arithmetic_<State> >,N> >))
                                  (scalar_< integer_<Data> >)
                                )
{
    typedef typename Value::value_type result_type;

    inline result_type
    operator()( Value const& v, State const&, Data const& p ) const
    {
      return v[p];
    }
  };
} } }

#endif
