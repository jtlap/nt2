//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_LOGICAL_XOR_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/logical_xor.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/bitwise_xor.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION
  ( boost::simd::tag::logical_xor_, boost::simd::tag::sse2_, (A0)
  , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
    ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
  )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
       return bitwise_cast<result_type>(b_xor(genmask<A0>(a0),
                                             genmask<A0>(a1)));
      }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION
  ( boost::simd::tag::logical_xor_, boost::simd::tag::sse2_, (A0)
  , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
    ((simd_<logical_<A0>,boost::simd::tag::sse_>))
  )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
       typedef typename A0::type type; 
       return bitwise_cast<result_type>(b_xor(bitwise_cast<type>(a0),
                                             bitwise_cast<type>(a1)));
      }
  };
} } }

#endif
