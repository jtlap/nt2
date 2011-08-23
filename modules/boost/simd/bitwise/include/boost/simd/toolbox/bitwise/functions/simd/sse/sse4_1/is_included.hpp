/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_SSE4_1_IS_INCLUDED_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_SSE4_1_IS_INCLUDED_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_, boost::simd::tag::sse4_1_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1) const
    {
      return _mm_testc_si128(a1, a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_, boost::simd::tag::sse4_1_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))
                              ((simd_<real_<A0>,X>))
                            )
  {
    typedef bool result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1) const
    {
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0; 
      return is_included(bitwise_cast<iA0>(a0), bitwise_cast<iA0>(a1));
    }
  };
  
} } }

#endif
#endif
