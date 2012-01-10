//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSSE3_HMSB_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSSE3_HMSB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/toolbox/reduction/functions/hmsb.hpp>
#include <boost/simd/include/functions/make.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hmsb_, boost::simd::tag::ssse3_,
                       (A0),
                       ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef uint32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef native<int8_t, boost::simd::tag::sse_> type8; 
      const type8 mask =  make<type8>( 0x1,0x3,0x5,0x7,0x9,0xB,0xD,0xF,
                                       0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
                                     
                               );
      type8 r = {_mm_shuffle_epi8(bitwise_cast<type8>(a0), mask)};
      return _mm_movemask_epi8(r); 
    }
  };
} } }
#endif
#endif
