//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ISQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ISQRT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/isqrt.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned integer 64
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::isqrt_, boost::simd::tag::avx_,
                       (A0),
                       ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return simd::bitwise_cast<A0>(boost::simd::toint(boost::simd::sqrt(boost::simd::tofloat(a0))));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is integer 64
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::isqrt_, boost::simd::tag::avx_,
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
                  , simd::bitwise_cast<int_type>(isqrt( simd::bitwise_cast<uint_type>(a0)))
                  );
    }
  };
} } }
#endif
#endif
