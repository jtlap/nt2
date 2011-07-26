//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_AVERAGE_HPP_INCLUDED
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/shrai.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                          ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                          ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
      //     A0 that = {_mm_avg_epu16(a0,a1)}; return that; //(a+b + 1) >> 1;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                          ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      return b_and(a0, a1)+shrai(b_xor(a0, a1),1);
      //     A0 that = {_mm_avg_epu8(a0,a1)}; return that; //  (a+b + 1) >> 1;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::average_, tag::cpu_,
                          (A0),
                          ((simd_<real_<A0>,boost::simd::tag::sse_>))
                          ((simd_<real_<A0>,boost::simd::tag::sse_>))
                         )
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
       return (a0+a1)*Half<A0>();
    }
  };
} } }
#endif
