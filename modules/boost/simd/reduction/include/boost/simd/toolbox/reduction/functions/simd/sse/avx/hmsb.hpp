//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_HMSB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_HMSB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <iostream> 
namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type8_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
				    )
  {
    typedef boost::simd::uint32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      return boost::simd::uint32_t(_mm_movemask_epi8(a00))|(boost::simd::uint32_t(_mm_movemask_epi8(a01)) << 16);
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type16_
  /////////////////////////////////////////////////////////////////////////////

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<type16_<A0>,boost::simd::tag::avx_>))
				    )
    {
      typedef boost::simd::uint32_t result_type; 
      BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
	{
	  typedef typename meta::scalar_of<A0>::type             sctype;
	  typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
	  svtype a00 = { _mm256_extractf128_si256(a0, 0)};
	  svtype a01 = { _mm256_extractf128_si256(a0, 1)};
	  return boost::simd::uint32_t(_mm_movemask_epi8(a00))|(boost::simd::uint32_t(_mm_movemask_epi8(a01)) << 16);
	  //TODO changeq that when hsmd sse will be correct for 16bits type
	}
    };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type64
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<type64_<A0>,boost::simd::tag::avx_>))
				    )
  {
    typedef boost::simd::uint32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	typedef native<double, boost::simd::tag::avx_> vdouble; 
	return bitwise_cast<boost::simd::uint32_t>(_mm256_movemask_pd(bitwise_cast<vdouble>(a0)));
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type32
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, boost::simd::tag::avx_,
				    (A0),
				    ((simd_<type32_<A0>,boost::simd::tag::avx_>))
				    )
  {
    typedef boost::simd::uint32_t result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
	typedef native<float, boost::simd::tag::avx_> vfloat; 
	return bitwise_cast<boost::simd::uint32_t>(_mm256_movemask_ps(bitwise_cast<vfloat>(a0)));
      }
  };
} } }
#endif
#endif
