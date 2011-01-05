//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_SSE_SSSE3_NEGATION_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negation_, tag::cpu_,
                           (A0),
                           ((simd_<uint32_<A0>,tag::sse_>))
                           ((simd_<uint32_<A0>,tag::sse_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::negation_(tag::simd_(tag::uint32_, tag::sse_),
                             tag::simd_(tag::uint32_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negation_, tag::cpu_,
                           (A0),
                           ((simd_<int32_<A0>,tag::sse_>))
                           ((simd_<int32_<A0>,tag::sse_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::negation_(tag::simd_(tag::int32_, tag::sse_),
                             tag::simd_(tag::int32_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negation_, tag::cpu_,
                           (A0),
                           ((simd_<int16_<A0>,tag::sse_>))
                           ((simd_<int16_<A0>,tag::sse_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::negation_(tag::simd_(tag::int16_, tag::sse_),
                             tag::simd_(tag::int16_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negation_, tag::cpu_,
                           (A0),
                           ((simd_<int8_<A0>,tag::sse_>))
                           ((simd_<int8_<A0>,tag::sse_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::negation_(tag::simd_(tag::int8_, tag::sse_),
                             tag::simd_(tag::int8_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::negation_, tag::cpu_,
                           (A0),
                           ((simd_<real_<A0>,tag::sse_>))
                           ((simd_<real_<A0>,tag::sse_>))
                          );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::negation_(tag::simd_(tag::real_, tag::sse_),
                             tag::simd_(tag::real_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
       /*PUT CODE HERE*/
    }
  };
} }

#endif
// modified by jt the 04/01/2011