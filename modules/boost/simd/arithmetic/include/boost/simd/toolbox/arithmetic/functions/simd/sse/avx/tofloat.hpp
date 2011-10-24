//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOFLOAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/arithmetic/functions/tofloat.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int32_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::tofloat_, boost::simd::tag::avx_,
                          (A0),
                          ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                         )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm256_cvtepi32_ps(a0)};
      return that;
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint32_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::tofloat_, boost::simd::tag::avx_,
                          (A0),
                          ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                         )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::scalar_of<result_type>::type stype;
      typedef native < stype, boost::simd::tag::sse_ > htype;
      
      htype h1 = make<htype>(a0[0],a0[1],a0[2],a0[3]);
      htype h2 = make<htype>(a0[4],a0[5],a0[6],a0[7]);
      result_type r = {_mm256_insertf128_ps(r, h1, 0)};
      r =  _mm256_insertf128_ps(r, h2, 1);
      return r; 
//       typedef typename meta::scalar_of<A0>::type stype;
//       typedef typename dispatch::meta::as_integer<A0,signed>::type sint_type;
//       static const sint_type hibitmask = integral_constant<sint_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const result_type offset = integral_constant<result_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const sint_type a00 = simd::native_cast<sint_type>(a0);
//       result_type v1 = {_mm256_cvtepi32_ps(a00)};
//       result_type v2 = {_mm256_cvtepi32_ps((b_andnot(a00, hibitmask)))};
//       v2 = v2+offset;
//       return select(isgez(a00),v1,v2);
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int64_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::tofloat_, boost::simd::tag::avx_,
                          (A0),
                          ((simd_<int64_<A0>,boost::simd::tag::avx_>))
                         )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return make<result_type>(a0[0], a0[1], a0[2], a0[3]);
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is uint64_t
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::tofloat_, boost::simd::tag::avx_,
                          (A0),
                          ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                         )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return make<result_type>(a0[0], a0[1], a0[2], a0[3]);
    }
  };
} } }

#endif
#endif
