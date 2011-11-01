//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_TYPED_BOOL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_TYPED_BOOL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/include/functions/complement.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_, 
                                   (A0), 
                                   ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                  )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cmpneq_pd(a0,Zero<A0>()) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cmpneq_ps(a0,Zero<A0>()) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cmpeq_epi8(a0,Zero<A0>()) };
      return complement(that);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cmpeq_epi16(a0,Zero<A0>()) };
      return complement(that);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm_cmpeq_epi32(a0,Zero<A0>()) };
      return complement(that);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::downgrade<A0, unsigned>::type  type;
      type tmp      = { a0 - Zero<A0>() };
      tmp           =  native_cast<type>(typed_bool(tmp));
      type tmp2     = { _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1)) };
      A0   that     = { tmp | tmp2 };
      return native_cast<result_type>(that);
    }
  };
} } }

#endif
#endif
