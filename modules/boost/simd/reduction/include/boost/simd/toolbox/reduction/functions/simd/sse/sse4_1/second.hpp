//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE4_1_SECOND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE4_1_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#ifdef BOOST_SIMD_ARCH_X86_64
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse4_1_,
                         (A0),
                         ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z = {_mm_extract_epi64(a0, 1)};
      return z;
    }
  };
} } }
#endif

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse4_1_,
                        (A0),
                        ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z ={ _mm_extract_epi32(a0,1)}; 
      return z; 
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse4_1_,
                        (A0),
                        ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z = { _mm_extract_epi16(a0,1)}; 
      return z; 
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::second_, boost::simd::tag::sse4_1_,
                        (A0),
                        ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type;
      type z = { _mm_extract_epi8(a0,1)}; 
      return z; 
    }
  };    
} } }
 
#endif
#endif
