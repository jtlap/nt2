//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE4_1_GROUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>

#define BOOST_SIMD_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_,(A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type    stype;
    typedef typename dispatch::meta::downgrade<stype>::type sftype;
    typedef simd::native<sftype,boost::simd::tag::sse_>        result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<result_type>::type itype;
      result_type z  = {_mm_cvtpd_ps(a1)};
      itype iz = simd::bitwise_cast<itype>(z);
      iz = _mm_slli_si128(iz, 8); 
      result_type r = simd::bitwise_cast<result_type>(iz);
      return b_or(r, simd::bitwise_cast<result_type>(_mm_cvtpd_ps(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION  (boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type         stype;
    typedef typename dispatch::meta::downgrade<stype>::type      utype;
    typedef simd::native<utype,boost::simd::tag::sse_>              result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::bitwise_cast<result_type>(_mm_packs_epi32(a0, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type    stype;
    typedef typename dispatch::meta::downgrade<stype>::type utype;
    typedef simd::native<utype,boost::simd::tag::sse_>         result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::bitwise_cast<result_type>(_mm_packs_epi16(a0, a1));
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type    stype;
    typedef typename dispatch::meta::downgrade<stype>::type utype;
    typedef simd::native<utype,boost::simd::tag::sse_>         result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      //_mm_packus_epi32 is sse4.1 specific
      return simd::bitwise_cast<result_type>(_mm_packus_epi32(a0, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                              ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type    stype;
    typedef typename dispatch::meta::downgrade<stype>::type utype;
    typedef simd::native<utype,boost::simd::tag::sse_>         result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return simd::bitwise_cast<result_type>(_mm_packus_epi16(a0, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::group_, boost::simd::tag::sse4_1_, (A0)
                            , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                              ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type    stype;
    typedef typename dispatch::meta::downgrade<stype>::type utype;
    typedef simd::native<utype,boost::simd::tag::sse_>         result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      // works only for int64 that are int32 representable
      result_type b = {_mm_slli_si128(simd::bitwise_cast<result_type>(a1),4)};
      b = b_or(b, a0);
      return simd::bitwise_cast<result_type>(_mm_shuffle_epi32(b, BOOST_SIMD_SH(0, 2, 1, 3)));
    }
  };
} } }

#undef BOOST_SIMD_SH

#endif
#endif
