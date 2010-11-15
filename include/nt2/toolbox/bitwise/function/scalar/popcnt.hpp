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

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),double,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      int64_t v = sbits(a0);
      return  __builtin_popcount( hi(v) )
            + __builtin_popcount( lo(v) );
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),float,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(sbits(a0));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),int64_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0 & 0xFF);   
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0 & 0xFFFF);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<popcnt_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0); //& Mone<A0>());
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
