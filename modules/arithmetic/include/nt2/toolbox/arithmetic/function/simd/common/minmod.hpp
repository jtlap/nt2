//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_MINMOD_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_MINMOD_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/sign.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minmod_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<arithmetic_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::minmod_(tag::simd_<tag::arithmetic_, X> ,
                           tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return b_and(nt2::min(a0, a1), is_gez(b_xor(a0, a1)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minmod_, tag::cpu_,
                         (A0)(X),
                         ((simd_<unsigned_<A0>,X>))
                         ((simd_<unsigned_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::minmod_(tag::simd_<tag::unsigned_, X> ,
                           tag::simd_<tag::unsigned_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return  nt2::min(a0,a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minmod_, tag::cpu_,
                         (A0)(X),
                         ((simd_<real_<A0>,X>))
                         ((simd_<real_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::minmod_(tag::simd_<tag::real_, X> ,
                           tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return b_or(b_or(is_nan(a0), is_nan(a1)),
		   b_and(nt2::min(a0,a1), is_gez(a0*a1))
		   );
    }
  };
} }

#endif
// modified by jt the 04/01/2011
