//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/include/functions/is_simd_logical.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::sse_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      BOOST_ASSERT_MSG(is_simd_logical(a0), "Some entries are not legal SIMD True or False"); 
      return boost::simd::native_cast<A1>(_mm_blendv_epi8( a2, a1
                                                  , boost::simd::native_cast<A1>(a0)
                                                  )
                                  );
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A1>,boost::simd::tag::sse_>))
                              ((simd_<single_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      //      assert(boolean_all(is_simd_logical(a0)))
      return boost::simd::native_cast<A1>(_mm_blendv_ps(a2, a1, boost::simd::native_cast<A1>(a0))); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::sse4_1_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A1>,boost::simd::tag::sse_>))
                              ((simd_<double_<A1>,boost::simd::tag::sse_>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      //      assert(boolean_all(is_simd_logical(a0)))
      return boost::simd::native_cast<A1>(_mm_blendv_pd(a2, a1, boost::simd::native_cast<A1>(a0))); 
    }
  };
} } }

#endif
#endif
