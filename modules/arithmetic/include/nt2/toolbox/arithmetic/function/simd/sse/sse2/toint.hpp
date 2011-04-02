//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOINT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOINT_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::toint_, tag::cpu_,
                        (A0),
                        ((simd_<arithmetic_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::toint_(tag::simd_<tag::arithmetic_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0>::type type; };

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::toint_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::toint_(tag::simd_<tag::double_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0>::type type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      typedef typename meta::scalar_of<type>::type stype;
      const type v = {{static_cast<stype>(a0[0]),static_cast<stype>(a0[1])}};
      return v;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::toint_, tag::cpu_,
                        (A0),
                        ((simd_<float_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::toint_(tag::simd_<tag::float_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      { typedef typename meta::as_integer<A0>::type type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type that =  {_mm_cvttps_epi32(a0)};
      return  that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011
