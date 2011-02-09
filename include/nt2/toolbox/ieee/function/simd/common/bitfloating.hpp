//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITFLOATING_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_BITFLOATING_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/select.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitfloating_, tag::cpu_,
                              (A0)(X),
                              ((simd_<arithmetic_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::bitfloating_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type type;
      //A0 s = Signmask<A0>();
      //      type that = {sel(isgez(type(a0)), a0, s-a0)};
      type r;
      A0 s = simd::native_cast<A0>(Signmask<type>());
      r = sel(is_gez(a0) , simd::native_cast<type>(a0), simd::native_cast<type>(s-a0));
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitfloating_, tag::cpu_,
                              (A0)(X),
                              ((simd_<unsigned_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::bitfloating_(tag::simd_<tag::unsigned_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type type;
      return simd::native_cast<type>(a0);
    }
  };
} }

#endif
// modified by jt the 04/01/2011