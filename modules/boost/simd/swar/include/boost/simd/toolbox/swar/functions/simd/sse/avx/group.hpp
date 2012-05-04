//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/swar/functions/group.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/include/constants/zero.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename dispatch::meta::downgrade<stype>::type                         utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                              type1;
      typedef simd::native<float,boost::simd::tag::avx_>                              type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef simd::native<float,boost::simd::tag::sse_ >   htype;
      htype r0 = {_mm256_cvtpd_ps(a0)};
      htype r1 = {_mm256_cvtpd_ps(a1)};
      rtype r  = {_mm256_insertf128_ps(r, r0, 0)};
      r = _mm256_insertf128_ps(r, r1, 1);
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                        ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      //     typedef typename meta::same<A0,boost::simd::tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      //      typedef typename meta::same<rtype,boost::simd::tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packs_epi32(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packs_epi32(a10, a11)};
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<int16_<A0>,boost::simd::tag::avx_>))
                        ((simd_<int16_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      //     typedef typename meta::same<A0,boost::simd::tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      //      typedef typename meta::same<rtype,boost::simd::tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packs_epi16(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packs_epi16(a10, a11)};
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                        ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packus_epi32(a00, a01)};

      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packus_epi32(a10, a11)};
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<int64_<A0>,boost::simd::tag::avx_>))
                        ((simd_<int64_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef simd::native<boost::simd::int32_t,boost::simd::tag::sse_ >   htype;
      typedef simd::native<boost::simd::int32_t,boost::simd::tag::avx_ >  i32type; 
//       i32type r0 = bitwise_cast < i32type>(a0);
//       i32type r1 = bitwise_cast < i32type>(a1);
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      htype v0 = {_mm_packus_epi32(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      htype v1 = {_mm_packus_epi32(a10, a11)};
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r; 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                        ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef simd::native<boost::simd::uint32_t,boost::simd::tag::sse_ >   htype;
      typedef simd::native<boost::simd::uint32_t,boost::simd::tag::avx_ >  ui32type; 
//       ui32type r0 = bitwise_cast < ui32type>(a0);
//       ui32type r1 = bitwise_cast < ui32type>(a1);
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      htype v0 = {_mm_packus_epi32(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      htype v1 = {_mm_packus_epi32(a10, a11)};
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r; 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<uint16_<A0>,boost::simd::tag::avx_>))
                        ((simd_<uint16_<A0>,boost::simd::tag::avx_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                        stype;
      typedef typename dispatch::meta::downgrade<stype>::type           utype;
      typedef simd::native<utype,boost::simd::tag::avx_>                type1;
      typedef simd::native<float,boost::simd::tag::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      //     typedef typename meta::same<A0,boost::simd::tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      //      typedef typename meta::same<rtype,boost::simd::tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packus_epi16(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packus_epi16(a10, a11)};
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::bitwise_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} } }
#endif
#endif
