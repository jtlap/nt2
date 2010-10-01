//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/exponentbits.hpp>
#include <nt2/include/functions/is_nez.hpp>

namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<exponent_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute exponent(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<exponent_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0, signed>::type  type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, signed>::type       result_type;
      typedef typename meta::scalar_of<A0>::type             s_type;
      typedef typename meta::scalar_of<result_type>::type sint_type;
      const int nmb= Nbmantissabits<s_type>();
      const result_type x = shri(exponentbits(a0), nmb);
      return x-b_and(Maxexponent<A0>(), is_nez(a0));
    }
  };
} }

      
#endif
