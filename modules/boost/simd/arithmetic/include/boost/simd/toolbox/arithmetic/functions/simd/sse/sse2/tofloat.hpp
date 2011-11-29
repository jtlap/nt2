//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/meta/size.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/maximum.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/make.hpp>

#include <boost/simd/toolbox/arithmetic/functions/simd/common/tofloat.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tofloat_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cvtepi32_ps(a0)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tofloat_, boost::simd::tag::sse2_ , (A0)
                            , ((simd_<uint64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type stype;
      return boost::simd::make<result_type>( static_cast<stype>(a0[0])
                              , static_cast<stype>(a0[1])
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tofloat_, boost::simd::tag::sse2_ , (A0)
                            , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type stype;

      return boost::simd::make<result_type>( static_cast<stype>(a0[0])
                              , static_cast<stype>(a0[1])
                              , static_cast<stype>(a0[2])
                              , static_cast<stype>(a0[3])
                              );
      //TO DO
 //      typedef typename meta::scalar_of<A0>::type stype;
//       typedef typename dispatch::meta::as_integer<A0,signed>::type sint_type;
//       //      static const sint_type hibitmask = integral_constant<sint_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const result_type offset = integral_constant<result_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const sint_type a00 = simd::bitwise_cast<sint_type>(a0);
//       result_type v1 = {_mm_cvtepi32_ps(a00)};
//       result_type v2 = {_mm_cvtepi32_ps((b_andnot(a00, Signmask<sint_type>())))};
//       v2 = v2+offset;
//       return select(is_gez(a00),v1,v2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::tofloat_, boost::simd::tag::sse2_ , (A0)
                            , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type sftype;
      if (maximum(abs(a0)) > boost::simd::Valmax<int32_t>())
      {
        return boost::simd::make<result_type>( static_cast<sftype>(a0[0])
                                , static_cast<sftype>(a0[1])
                                );
      }
      typedef typename boost::simd::meta::int32_t_<A0>::type htype;
      result_type v = { _mm_cvtepi32_pd(_mm_shuffle_epi32(a0,_MM_SHUFFLE(3,1,2,0)))};
      return v;
    }
  };
} } }

#endif
#endif
