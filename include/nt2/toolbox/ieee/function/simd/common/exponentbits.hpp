//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EXPONENTBITS_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EXPONENTBITS_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
//



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::exponentbits_, tag::cpu_,
                               (A0)(X),
                               ((simd_<arithmetic_<A0>,X>))
                              );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::exponentbits_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0, signed>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, signed>::type result_type;
      typedef typename meta::scalar_of<A0>::type             s_type;
      typedef typename meta::scalar_of<result_type>::type sint_type;
      const sint_type me = Maxexponent<s_type>();
      const sint_type nmb= Nbmantissabits<s_type>();
      const result_type Mask = splat<result_type>((2*me+1)<<nmb);
      return (b_and(Mask, a0));
    }

  };
} }

#endif
// modified by jt the 04/01/2011