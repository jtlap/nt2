/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED

#include <nt2/sdk/dsl/literal.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register terminal handlers for SIMD expression - native case
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::terminal_,tag::cpu_
                            , (Value)(State)(Data)(X)(Y)
                            , ((simd_<arithmetic_<Value>,X>))
                              ((target_<simd_<arithmetic_<State>,Y> >))
                              (integer_<Data>)
                            )
  {
    typedef typename meta::strip<Value>::type::parent result_type;

    inline result_type
    operator()( Value& v, State const& , Data const&  ) const
    {
      return v.value();
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register terminal handlers for SIMD expression - emulated case
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL(  tag::terminal_,tag::cpu_
                                , (class Value)(class State)
                                  (class Data)(std::size_t N)
                                , ((array_<arithmetic_<Value>,N>))
                                  ((target_<array_<arithmetic_<State>,N> >))
                                  (integer_<Data>)
                                )
{
    typedef typename meta::strip<Value>::type::parent::value_type result_type;

    inline result_type
    operator()( Value& v, State const&, Data const& p ) const
    {
      return v[p];
    }
  };
} }

#endif
