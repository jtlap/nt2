//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::avx_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
     return b_or(b_and(a1,a0),b_andnot(a2,a0));
    }
  };
} } }


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::avx_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<float_<A1>,X>))
                              ((simd_<float_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_ps(a2, a1, boost::simd::native_cast<A1>(a0))); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::select_, boost::simd::tag::avx_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<double_<A1>,X>))
                              ((simd_<double_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_pd(a2, a1, boost::simd::native_cast<A1>(a0))); 
    }
  };
} } }

#endif
#endif
