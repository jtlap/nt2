/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE4_1_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE4_1_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT
#include <boost/simd/toolbox/operator/functions/multiplies.hpp>
#include <boost/simd/toolbox/operator/functions/simd/sse/sse4_1/multiplies.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, boost::simd::tag::sse4_1_
                            , (A0)
                            , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                              ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_mullo_epi32(a0, a1);
    }
  };
} } }


#endif
#endif
