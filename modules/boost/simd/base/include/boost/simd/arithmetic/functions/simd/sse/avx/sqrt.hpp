//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_SQRT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/arithmetic/functions/sqrt.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sqrt_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<double_<A0>,boost::simd::tag::avx_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm256_sqrt_pd(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sqrt_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<single_<A0>,boost::simd::tag::avx_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm256_sqrt_ps(a0);
    }
  };
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned integer 64
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sqrt_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return boost::simd::touint(boost::simd::sqrt(boost::simd::tofloat(a0)));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is integer 64
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sqrt_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<int64_<A0>,boost::simd::tag::avx_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0,signed>::type     int_type;
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type  uint_type;
      return if_else_zero( is_gtz(a0)
                         , boost::simd::toint(boost::simd::sqrt(boost::simd::tofloat(a0)))
                         );
    }
  };
} } }
#endif
#endif
