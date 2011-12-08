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
      //TO DO proper implementation
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
