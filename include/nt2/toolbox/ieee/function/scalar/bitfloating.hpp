//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for bitfloating

  /////////////////////////////////////////////////////////////////////////////
  // Compute bitfloating(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<bitfloating_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> { typedef typename meta::as_real<A0>::type type; };

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (unsigned,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,    unsigned)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type rtype;
      typename meta::from_bits<rtype, signed>::type  that =  {a0};
      return that.value; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type rtype;
      typedef typename meta::from_bits<rtype>::type  type;
      type that =  {a0>=Zero<A0>()?a0:((1LL << (8*sizeof(A0)-1))-a0)};//TOVERIFY PERFS
      return that.value; 
    }
  };
} }


      
#endif
