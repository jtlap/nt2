//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/minimum.hpp>
#include <boost/simd/include/functions/maximum.hpp>
#include <boost/simd/include/functions/make.hpp>
#define BOOST_SIMD_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
#define BOOST_SIMD_CAST(T, a)   simd::bitwise_cast<T>(a)    
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sort_, boost::simd::tag::sse2_,
                       (A0),
                       ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type flt;
      A0 a =  {a0()};
      A0 b =  {BOOST_SIMD_CAST(A0, _mm_movehl_ps(BOOST_SIMD_CAST(flt, a0), BOOST_SIMD_CAST(flt, a0)))};
      comp(a, b);
      a = BOOST_SIMD_CAST(A0, _mm_movelh_ps(BOOST_SIMD_CAST(flt, a), BOOST_SIMD_CAST(flt, b)));
      b = BOOST_SIMD_CAST(A0, _mm_shuffle_ps(BOOST_SIMD_CAST(flt, a), BOOST_SIMD_CAST(flt, b), BOOST_SIMD_SH(1, 3, 1, 3)));
      comp(a, b);
      A0 c = {BOOST_SIMD_CAST(A0, _mm_movelh_ps(BOOST_SIMD_CAST(flt, b), BOOST_SIMD_CAST(flt, b)))};
      A0 d = {a()};
      comp(c, d);
      a = BOOST_SIMD_CAST(A0, _mm_shuffle_ps(BOOST_SIMD_CAST(flt, c), BOOST_SIMD_CAST(flt, a), BOOST_SIMD_SH(3, 2, 0, 0)));
      b = BOOST_SIMD_CAST(A0, _mm_movehl_ps(BOOST_SIMD_CAST(flt, b), BOOST_SIMD_CAST(flt, d)));
      b = BOOST_SIMD_CAST(A0, _mm_shuffle_ps(BOOST_SIMD_CAST(flt, a), BOOST_SIMD_CAST(flt, b), BOOST_SIMD_SH(3, 1, 0, 2)));
      return b;
    }
  private :
    template < class T > static inline void comp(T & a,T & b)
    {
      T c =  boost::simd::min(a, b);
      b = boost::simd::max(a, b);
      a = c;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sort_, boost::simd::tag::sse2_,
                       (A0),
                       ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return boost::simd::make<A0>(minimum(a0), maximum(a0));
    }
  };
} } }
#endif
#endif
