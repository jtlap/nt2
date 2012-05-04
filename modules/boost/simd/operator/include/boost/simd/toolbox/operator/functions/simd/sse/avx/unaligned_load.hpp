//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_UNALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// unaligned_load for AVX SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/toolbox/operator/functions/unaligned_load.hpp>
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
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< double_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< double_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      result_type that = { _mm256_loadu_pd(a0+a1) };
      return that;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)
                            , (iterator_< scalar_< double_<A0> > >)
                              ((target_< simd_< double_<A1>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type that = { _mm256_loadu_pd(a0) };
      return that;
    }
  };
} } }

//==============================================================================
// unaligned_load vector of float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< single_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< single_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      result_type that = {_mm256_loadu_ps(a0+a1)};
      return that;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)
                            , (iterator_< scalar_< single_<A0> > >)
                              ((target_< simd_< single_<A1>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type that = {_mm256_loadu_ps(a0)};
      return that;
    }
  };
} } }

//==============================================================================
// unaligned_load vector of integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< integer_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< integer_<A2>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      result_type that = { _mm256_loadu_si256(reinterpret_cast<__m256i const*>(a0+a1)) };
      return that;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_ , boost::simd::tag::avx_
                            , (A0)(A1)
                            , (iterator_< scalar_< integer_<A0> > >)
                              ((target_< simd_< integer_<A1>, boost::simd::tag::avx_ > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&)const
    {
      result_type that = { _mm256_loadu_si256(reinterpret_cast<__m256i const*>(a0)) };
      return that;
    }
  };
} } }

#endif
#endif
