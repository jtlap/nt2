//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/lo.hpp>
#include <nt2/include/functions/hi.hpp>
#include <nt2/include/functions/sbits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for popcnt

  /////////////////////////////////////////////////////////////////////////////
  // Compute popcnt(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<popcnt_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (6, (double,float,int64_t,int8_t,int16_t,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
    {
      int64_t v = sbits(a0);
      return  __builtin_popcount( hi(v) )
            + __builtin_popcount( lo(v) );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       float)
    {
      return __builtin_popcount(sbits(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int64_t)
    {
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,      int8_t)
    {
      return __builtin_popcount(a0 & 0xFF);   
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,     int16_t)
    {
      return __builtin_popcount(a0 & 0xFFFF);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return __builtin_popcount(a0); //& Mone<A0>());
    }
   };
} }


      
#endif
