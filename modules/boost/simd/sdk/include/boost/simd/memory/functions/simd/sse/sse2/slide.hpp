//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_SLIDE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - slide between scalar values
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::sse2_
                                    , (A0)(N)
                                    , ((simd_< arithmetic_<A0>
                                            , boost::simd::tag::sse_
                                            >
                                      ))
                                      ((simd_< arithmetic_<A0>
                                            , boost::simd::tag::sse_
                                            >
                                      ))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, N const&) const
    {
      // Compute relative offsets for shifted loads pair
      static const std::size_t cardinal = meta::cardinal_of<A0>::value;
      static const std::size_t shifta   = (16u/cardinal)*(N::value);
      static const std::size_t shiftb   = (16u/cardinal)*(cardinal-N::value);

      // Shift everything in place
      __m128i sa = _mm_srli_si128(bitwise_cast<__m128i>(a0),shifta);
      __m128i sb = _mm_slli_si128(bitwise_cast<__m128i>(a1),shiftb);

      return bitwise_cast<result_type>(_mm_or_si128(sa,sb));
    }
  };
} } }

#endif
#endif
