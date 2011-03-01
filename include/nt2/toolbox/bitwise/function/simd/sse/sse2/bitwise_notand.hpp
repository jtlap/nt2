//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_BITWISE_NOTAND_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_BITWISE_NOTAND_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::bitwise_notand_, tag::cpu_,
			 (A0)(A1),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::bitwise_notand_(tag::simd_<tag::arithmetic_,tag::sse_>, tag::simd_<tag::arithmetic_,tag::sse_>)), 
			 ((simd_<arithmetic_<A0>,tag::sse_>))
			 ((simd_<arithmetic_<A1>,tag::sse_>))
                       );


namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitwise_notand_(tag::simd_<tag::arithmetic_, tag::sse_>,
                                   tag::simd_<tag::arithmetic_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer< A0 >::type int_type;
      int_type t0 = simd::native_cast<int_type>( a0 );
      int_type t1 = simd::native_cast<int_type>( a1 );
      A0     that = { simd::native_cast<A0>(_mm_andnot_si128(t0,t1)) };
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitwise_notand_, tag::cpu_,
                                 (A0),
                                 ((simd_<double_<A0>,tag::sse_>))
                                 ((simd_<double_<A0>,tag::sse_>))
                                );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitwise_notand_(tag::simd_<tag::double_, tag::sse_>,
                                   tag::simd_<tag::double_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that;
      that = a1;
      that =  _mm_andnot_pd(a0, that);
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitwise_notand_, tag::cpu_,
                                 (A0),
                                 ((simd_<float_<A0>,tag::sse_>))
                                 ((simd_<float_<A0>,tag::sse_>))
                                );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitwise_notand_(tag::simd_<tag::float_, tag::sse_>,
                                   tag::simd_<tag::float_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that;
      that = a1;
      that = _mm_andnot_ps(a0,that);
      return that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011
