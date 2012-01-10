//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/average.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_xor.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/shrai.hpp>
#include <boost/simd/include/constants/half.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, boost::simd::tag::sse2_,
                          (A0),
                          ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                          ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, boost::simd::tag::sse2_,
                          (A0),
                          ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                          ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, boost::simd::tag::sse2_,
                          (A0),
                          ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                          ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, boost::simd::tag::sse2_,
                          (A0),
                          ((simd_<floating_<A0>,boost::simd::tag::sse_>))
                          ((simd_<floating_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
       return (a0+a1)*boost::simd::Half<A0>();
    }
  };
} } }
#endif
#endif
