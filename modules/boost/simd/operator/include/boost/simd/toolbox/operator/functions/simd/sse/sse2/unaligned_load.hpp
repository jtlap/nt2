//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_UNALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// unaligned_load for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

//==============================================================================
// unaligned_load vector of double
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(X)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              ((target_< simd_< double_<A1>, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type
      that = { _mm_loadu_pd(a0) };
      return that;
    }
  };
} } }

//==============================================================================
// unaligned_load vector of float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(X)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              ((target_< simd_< single_<A1>, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type
      that = { _mm_loadu_ps(a0) };
      return that;
    }
  };
} } }

//==============================================================================
// unaligned_load vector of integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::sse2_
                            , (A0)(A1)(X)
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              ((target_< simd_< integer_<A1>,X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type
      that = { _mm_loadu_si128(reinterpret_cast<__m128i const*>(a0)) };
      return that;
    }
  };
} } }

#endif
#endif
