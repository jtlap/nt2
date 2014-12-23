//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMMAX_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMMAX_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/cummax.hpp>
#include <boost/simd/swar/include/functions/shuffle.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <nt2/table.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT         (cummax_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 tmp = max(a0,  shuffle<0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14>(a0));
      tmp =    max(tmp, shuffle<0,1,1,1,4,4,4,5,6,7,8,9,10,11,12,13>(tmp));
      tmp =    max(tmp, shuffle<0,1,2,3,3,3,3,3,4,5,6,7,8,9,10,11>(tmp));
      return   max(tmp, shuffle<0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,7>(tmp));
    }
  };

  BOOST_DISPATCH_IMPLEMENT         (cummax_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return max(a0, shuffle<0,0>(a0));
    }
  };

  BOOST_DISPATCH_IMPLEMENT         (cummax_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
       A0 tmp = max(a0,  shuffle<0,0,1,2,3,4,5,6>(a0));
       tmp =    max(tmp, shuffle<0,1,1,1,4,4,4,5>(tmp));
       return   max(tmp, shuffle<0,1,2,3,3,3,3,3>(tmp));
    }
  };

  BOOST_DISPATCH_IMPLEMENT         (cummax_, boost::simd::tag::sse2_,
                                    (A0),
                                    ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 tmp = max(a0,  shuffle<0,0,1,2>(a0));
      return   max(tmp, shuffle<0,1,1,1>(tmp));
    }
  };
} } }
#endif
#endif
