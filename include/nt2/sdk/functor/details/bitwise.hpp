/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_BITWISE_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_BITWISE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// bitwise operators extended implementation
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // bitwise operators on scalar arithmetic types works on real types too
  //////////////////////////////////////////////////////////////////////////////
  template<class Info> struct call<bitwise_and_,tag::scalar_(tag::arithmetic_),Info>                        
  {                                                                   
    template<class Sig> struct result;                                    
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};
    
    NT2_FUNCTOR_CALL_DISPATCH( 2, A0, (2, (real_,integer_)))

    NT2_FUNCTOR_CALL_EVAL_IF(2, real_)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      typename meta::as_bits<A1>::type t1 = {a1};
      t0.bits &= t1.bits;
      return t0.value;
    }     

    NT2_FUNCTOR_CALL_EVAL_IF(2, integer_)
    {
      return a0 & a1;
    }     
  };

  template<class Info> struct call<bitwise_or_,tag::scalar_(tag::arithmetic_),Info>                        
  {                                                                   
    template<class Sig> struct result;                                    
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};
    
    NT2_FUNCTOR_CALL_DISPATCH( 2, A0, (2, (real_,integer_)))

    NT2_FUNCTOR_CALL_EVAL_IF(2, real_)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      typename meta::as_bits<A1>::type t1 = {a1};
      t0.bits |= t1.bits;
      return t0.value;
    }     

    NT2_FUNCTOR_CALL_EVAL_IF(2, integer_)
    {
      return a0 | a1;
    }     
  };

  template<class Info> struct call<bitwise_xor_,tag::scalar_(tag::arithmetic_),Info>                        
  {                                                                   
    template<class Sig> struct result;                                    
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};
    
    NT2_FUNCTOR_CALL_DISPATCH( 2, A0, (2, (real_,integer_)))

    NT2_FUNCTOR_CALL_EVAL_IF(2, real_)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      typename meta::as_bits<A1>::type t1 = {a1};
      t0.bits ^= t1.bits;
      return t0.value;
    }     

    NT2_FUNCTOR_CALL_EVAL_IF(2, integer_)
    {
      return a0 ^ a1;
    }     
  };  
} }

#endif
