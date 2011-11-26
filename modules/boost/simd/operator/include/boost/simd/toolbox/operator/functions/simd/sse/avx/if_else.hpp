//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/operator/functions/if_else.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_ps(a2, a1,  native_cast<A1>(genmask(a0)))); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_pd(a2, a1, native_cast<A1>(genmask(a0)))); 
    }
  };
} } }
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_ps(a2, a1, native_cast<A1>(a0))); 
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::native_cast<A1>(_mm256_blendv_pd(a2, a1, native_cast<A1>(a0))); 
    }
  };
} } }

#endif
#endif

