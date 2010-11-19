//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENTBITS_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_EXPONENTBITS_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>


namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<exponentbits_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result; 
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute exponentbits(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<exponentbits_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, signed>{}; 
      

    NT2_FUNCTOR_CALL(1)
    {
      typedef  typename NT2_CALL_RETURN_TYPE(1)::type int_type;
      static const int_type me = Maxexponent<A0>();
      static const int_type nmb= Nbmantissabits<A0>();
      static const int_type Mask = (2*me+1)<<nmb;
      return b_and(Mask, a0);
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
