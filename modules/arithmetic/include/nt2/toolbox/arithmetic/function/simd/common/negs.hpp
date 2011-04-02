//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_NEGS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_NEGS_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is signed_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negs_, tag::cpu_,
                       (A0)(X),
                       ((simd_<signed_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::negs_(tag::simd_<tag::signed_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return sel(eq(a0, Valmin<A0>()), Valmax<A0>(), -a0); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negs_, tag::cpu_,
                       (A0)(X),
                       ((simd_<real_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::negs_(tag::simd_<tag::real_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return -a0; 
    }
  };
} }

#endif
