//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_REVERSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/swar/functions/reverse.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return _mm_shuffle_ps(a0, a0, 0x1B);
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        return _mm_shuffle_pd(a0, a0, 0x1);
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type8_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef typename dispatch::meta::upgrade<A0>::type         r_type;
        r_type tmp1, tmp2; 
        boost::simd::split(a0, tmp1, tmp2);
        return boost::simd::group(reverse(tmp2), reverse(tmp1)); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type64_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef typename dispatch::meta::as_floating<A0>::type rtype;
        return  simd::bitwise_cast<A0>(reverse( simd::bitwise_cast<rtype>(a0))); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type16_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef typename dispatch::meta::upgrade<A0>::type         r_type;
        r_type tmp1, tmp2; 
        boost::simd::split(a0, tmp1, tmp2);
        return boost::simd::group(reverse(tmp2), reverse(tmp1)); 
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is type32_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reverse_, boost::simd::tag::sse2_
                                     , (A0)
                                     , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
        typedef typename dispatch::meta::as_floating<A0>::type rtype;
        return  simd::bitwise_cast<A0>(reverse( simd::bitwise_cast<rtype>(a0))); 
      }
  };
} } }


#endif
#endif
