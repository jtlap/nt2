//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_DIVS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_DIVS_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/functions/rdivide.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::divs_, tag::cpu_,
                       (A0)(X),
                       ((simd_<unsigned_<A0>,X>))((simd_<unsigned_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::divs_(tag::simd_<tag::unsigned_, X>,
			 tag::simd_<tag::unsigned_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::rdivide(a0, a1); 
    }
  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::divs_, tag::cpu_,
                       (A0)(X),
                       ((simd_<integer_<A0>,X>))((simd_<integer_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::divs_(tag::simd_<tag::integer_, X>,
			 tag::simd_<tag::integer_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      A0 c = b_and(eq(a0, Valmin<A0>()), eq(a1, Mone<A0>())); 
      return rdivide( a0-c, a1); 
    }
  };
} }
#endif
