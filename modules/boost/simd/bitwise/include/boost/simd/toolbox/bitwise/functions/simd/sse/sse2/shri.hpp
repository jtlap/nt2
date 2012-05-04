//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_SSE2_SHRI_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/bitwise/functions/shri.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/constants/digits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shri_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef native<typename boost::simd::meta::int32_t_<A0>::type, boost::simd::tag::sse_> gen_type;
      result_type const Mask1 =  bitwise_cast<result_type>(boost::simd::integral_constant<gen_type, 0x00ff00ff>());
      result_type const Mask2 =  bitwise_cast<result_type>(boost::simd::integral_constant<gen_type, 0xff00ff00>());
      result_type tmp  = b_and(a0, Mask1);
      result_type tmp1 = {_mm_srli_epi16(tmp, a1)};
      tmp1 = b_and(tmp1, Mask1);
      tmp = b_and(a0, Mask2);
      result_type tmp3 = {_mm_srli_epi16(tmp, a1)};
      return tmp1 | b_and(tmp3, Mask2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::shri_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      sint const that = { _mm_srli_epi32(bitwise_cast<sint>(a0), int(a1))};
      return bitwise_cast<A0>(that);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shri_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type sint;
      sint const that ={ _mm_srli_epi64(bitwise_cast<sint>(a0), int(a1))};
      return bitwise_cast<result_type>(that);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shri_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = {_mm_srli_epi16(a0, int(a1))};
      return that;
    }
  };
} } }

#endif
#endif
