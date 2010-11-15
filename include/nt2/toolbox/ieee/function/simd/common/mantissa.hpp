//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_MANTISSA_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/select.hpp>



namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<mantissa_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute mantissa(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<mantissa_,tag::simd_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, unsigned>::type  int_type;
      typedef typename meta::scalar_of<int_type>::type      sint_type;
      typedef typename meta::scalar_of<A0>::type               s_type;
      const sint_type n1 = ((2*Maxexponent<s_type>()+1)<<Nbmantissabits<s_type>());
      const sint_type n2 = (sizeof(sint_type)-2);
      const int_type  mask0 = (splat<int_type>((n1<<2)>>2));
      const int_type  mask1 = (splat<int_type>((~n1)|n2));
      return sel(is_eqz(a0),a0,b_or(b_and(a0,mask1),mask0));
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
