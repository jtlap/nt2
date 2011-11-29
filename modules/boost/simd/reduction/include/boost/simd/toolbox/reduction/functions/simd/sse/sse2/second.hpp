//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_SECOND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type type;
      int that = _mm_extract_epi16(a0, 0);
      return (that >> 8) & 0xFF;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<double_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type type;
      typedef typename dispatch::meta::as_floating<A0>::type rtype;
      const type tmp = bitwise_cast<type>(a0);
      const type tmp1= {_mm_srli_si128(tmp, 8)}; 
      const rtype z = bitwise_cast<rtype>(tmp1); 
      return _mm_cvtsd_f64(z);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<single_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
       typedef typename dispatch::meta::as_integer<A0>::type itype;
       typedef typename meta::scalar_of<itype>::type sitype;
       return bitwise_cast<result_type>(_mm_cvtsi128_si32(_mm_srli_si128(bitwise_cast<itype>(a0), 4)));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints32_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type type;
      return _mm_cvtsi128_si32(_mm_srli_si128(simd::bitwise_cast<type>(a0), 4));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type type;
      typedef typename dispatch::meta::as_floating<A0>::type rtype;
      return bitwise_cast<result_type, double >(_mm_cvtsd_f64(bitwise_cast<rtype>(_mm_srli_si128(bitwise_cast<type>(a0), 8)))); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse2_,
                         (A0),
                         ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm_extract_epi16(a0, 1);
    }
  };
} } }
#endif
#endif
