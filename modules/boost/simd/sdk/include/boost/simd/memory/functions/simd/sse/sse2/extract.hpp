//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_EXTRACT_HPP_INCLUDED
#ifndef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/extract.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< ints8_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      int v = _mm_extract_epi16(a0, A1::value / 2);
      if(A1::value % 2 == 0)
        return result_type(v & 0xFF);
      else
        return result_type((v >> 8) & 0xFF);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< ints16_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_extract_epi16(a0, A1::value));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< ints32_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_cvtsi128_si32(_mm_srli_si128(a0, A1::value * 4)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< ints64_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_cvtsi128_si64(_mm_srli_si128(a0, A1::value * 8)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(a0), A1::value * 4)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_< double_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return _mm_cvtss_f64(_mm_castsi128_pd(_mm_srli_si128(_mm_castpd_si128(a0), A1::value * 8)));
    }
  };

} } }

#endif
#endif
