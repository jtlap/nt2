//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_SUBS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_SUBS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/simd/common/subs.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<uint16_<A0>,boost::simd::tag::sse_>))((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::native_cast<A0>(_mm_subs_epu16(a0, a1)); 
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::subs_, boost::simd::tag::sse2_,
			     (A0),
			     ((simd_<int16_<A0>,boost::simd::tag::sse_>))
			     ((simd_<int16_<A0>,boost::simd::tag::sse_>))
			     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::native_cast<A0>(_mm_subs_epi16(a0, a1)); 
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint8_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, boost::simd::tag::sse2_
			      , (A0)
			      , ((simd_<uint8_<A0>,boost::simd::tag::sse_>))((simd_<uint8_<A0>,boost::simd::tag::sse_>))
			      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
	return simd::native_cast<A0>(_mm_subs_epu8(a0, a1)); 
      }
  };
  
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, boost::simd::tag::sse2_
			      , (A0)
			      , ((simd_<int8_<A0>,boost::simd::tag::sse_>))((simd_<int8_<A0>,boost::simd::tag::sse_>))
			      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::native_cast<A0>(_mm_subs_epi8(a0, a1)); 
    }
  };
} } }


#endif
#endif
