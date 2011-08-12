//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_ANDNOT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/strip.hpp>

#include <boost/simd/include/functions/details/simd/sse/sse4_1/bitwise_andnot.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::bitwise_andnot_, boost::simd::tag::avx_,
                                 (A0),
                                 ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                 ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<boost::simd::tag::bitwise_andnot_(tag::simd_<tag::arithmetic_, tag::avx_),
                                   boost::simd::tag::simd_<tag::arithmetic_, tag::avx_)),
              boost::simd::boost::simd::tag::avx_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::double_<A0>::type dtype;
      return simd::native_cast<A0>(b_andnot(simd::native_cast<simd::native<dtype, simd::avx_> >(a0),
                               simd::native_cast<simd::native<dtype, simd::avx_> >(a1)));
    }
  };
} } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::bitwise_andnot_, boost::simd::tag::avx_,
                                 (A0),
                                 ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                 ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<boost::simd::tag::bitwise_andnot_(tag::simd_<tag::double_, tag::avx_),
                                   boost::simd::tag::simd_<tag::double_, tag::avx_)),
              boost::simd::boost::simd::tag::avx_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_andnot_pd(simd::native_cast<A0>(a1), a0)};
      return that;
    }
  };
} } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::bitwise_andnot_, boost::simd::tag::avx_,
                                 (A0),
                                 ((simd_<float_<A0>,boost::simd::tag::avx_>))
                                 ((simd_<float_<A0>,boost::simd::tag::avx_>))
                                );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<boost::simd::tag::bitwise_andnot_(tag::simd_<tag::float_, tag::avx_),
                                   boost::simd::tag::simd_<tag::float_, tag::avx_)),
              boost::simd::boost::simd::tag::avx_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_andnot_ps(simd::native_cast<A0>(a1), a0)};
      return that;
    }
  };
} } }

#endif
#endif
