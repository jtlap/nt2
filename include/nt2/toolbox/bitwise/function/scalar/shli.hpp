//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHLI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHLI_HPP_INCLUDED
#include <nt2/sdk/meta/as_bits.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<shli_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::is_integral<typename meta::strip<A1>::type >{}; 
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute shli(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<shli_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
       struct result<This(A0,A1)> : meta::strip <A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typedef typename meta::as_bits<A0>::type type;
      type that = {a0};
      that.bits <<= a1;
      return that.value;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,    arithmetic_)
    {
      typedef typename meta::as_bits<A0>::type type;
      type that = {a0};
      that.bits <<= a1;
      return that.value;
    }
   };
} }


      
#endif
