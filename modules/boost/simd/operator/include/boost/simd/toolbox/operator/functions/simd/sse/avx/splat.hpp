//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SPLAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/include/functions/make.hpp>

//==============================================================================
// Implementation when type A0 is double
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< double_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<double , boost::simd::tag::sse_ >  htype;
      const htype hres = {_mm_set1_pd(double(a0))}; 
      result_type that = { _mm256_insertf128_pd(that, hres, 0)};
      that =  _mm256_insertf128_pd(that,hres, 1);
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< float_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<float , boost::simd::tag::sse_ >  htype;
      const htype hres = {_mm_set1_ps(float(a0))}; 
      result_type that = { _mm256_insertf128_ps(that, hres, 0)};
      that =  _mm256_insertf128_ps(that,hres, 1);
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints8
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints8_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<boost::simd::int8_t , boost::simd::tag::sse_ >  htype;
      const htype hres = {_mm_set1_epi8(a0)}; 
      result_type that = { _mm256_insertf128_si256(that, hres, 0)};
      that =  _mm256_insertf128_si256(that,hres, 1);
      return that; 
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints16
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints16_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<boost::simd::int16_t , boost::simd::tag::sse_ >  htype;
      const htype hres = {_mm_set1_epi16(a0)}; 
      result_type that = { _mm256_insertf128_si256(that, hres, 0)};
      that =  _mm256_insertf128_si256(that,hres, 1);
      return that; 
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints32
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints32_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<boost::simd::int32_t , boost::simd::tag::sse_ >  htype;
      const htype hres = {_mm_set1_epi32(a0)}; 
      result_type that = { _mm256_insertf128_si256(that, hres, 0)};
      that =  _mm256_insertf128_si256(that,hres, 1);
      return that; 
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints64
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints64_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef simd::native<boost::simd::int64_t , boost::simd::tag::sse_ >  htype;
      typedef simd::native<double , boost::simd::tag::sse_ >  fhtype;
      typedef simd::native<double , boost::simd::tag::avx_ >  ftype; 
      const htype hres = splat<htype>(a0);
      const fhtype fhres =  bitwise_cast<fhtype>(hres); 
      ftype that = { _mm256_insertf128_pd(that, fhres, 0)};
      that =  _mm256_insertf128_pd(that,fhres, 1);
      return bitwise_cast<result_type>(that);
    }
  };
} } }

#endif
#endif
