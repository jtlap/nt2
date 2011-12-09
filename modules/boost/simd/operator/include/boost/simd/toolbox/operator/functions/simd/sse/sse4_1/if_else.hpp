//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE4_1_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE4_1_IF_ELSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/toolbox/operator/functions/if_else.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A1>,boost::simd::tag::sse_>))
                              ((simd_<single_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return bitwise_cast<result_type>(_mm_blendv_ps(a2, a1, genmask(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A1>,boost::simd::tag::sse_>))
                              ((simd_<double_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return bitwise_cast<result_type>(_mm_blendv_pd(a2, a1, genmask(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                              ((simd_<integer_<A1>,boost::simd::tag::sse_>))
                              ((simd_<integer_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return bitwise_cast<A1>(_mm_blendv_epi8(a2, a1, genmask(a0)));
    }
  };
} } }

#endif
#endif
