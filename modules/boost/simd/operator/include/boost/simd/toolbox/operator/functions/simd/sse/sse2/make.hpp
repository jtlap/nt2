//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MAKE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

//==============================================================================
// make for double
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< double_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template<class I0, class I1>
    inline result_type operator()(I0 const& a0, I1 const& a1) const
    {
      result_type that = { _mm_setr_pd(a0, a1) };
      return that;
    }
  };
} } }

//==============================================================================
// make for 64bits integers
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< ints64_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template<class I0, class I1>
    inline result_type operator()(I0 const& a0, I1 const& a1) const
    {
      result_type
      that =  { _mm_setr_epi32( (uint64_t(a0) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a0) & 0xFFFFFFFF00000000ULL) >> 32
                              , (uint64_t(a1) & 0x00000000FFFFFFFFULL)
                              , (uint64_t(a1) & 0xFFFFFFFF00000000ULL) >> 32
                            )
              };
      return that;
    }
  };
} } }

//==============================================================================
// make for float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< float_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template<class I0, class I1,class I2,class I3> inline result_type
    operator()(I0 const& a0, I1 const& a1, I2 const& a2, I3 const& a3) const
    {
      result_type that = { _mm_setr_ps(a0, a1, a2, a3) };
      return that;
    }
  };
} } }

//==============================================================================
// make for 32 bits integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< ints32_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template<class I0, class I1,class I2,class I3> inline result_type
    operator()(I0 const& a0, I1 const& a1, I2 const& a2, I3 const& a3) const
    {
      result_type that = { _mm_setr_epi32(a0, a1, a2, a3) };
      return that;
    }
  };
} } }

//==============================================================================
// make for 16 bits integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< ints16_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template< class I0, class I1,class I2,class I3
            , class I4, class I5,class I6,class I7
            >  inline result_type
    operator()( I0 const& a0, I1 const& a1, I2 const& a2, I3 const& a3
              , I4 const& a4, I5 const& a5, I6 const& a6, I7 const& a7
              ) const
    {
      result_type that = { _mm_setr_epi16(a0, a1, a2, a3 , a4, a5, a6, a7 ) };
      return that;
    }
  };
} } }

//==============================================================================
// make for 8 bits integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, boost::simd::tag::sse2_, (A0)
                            , ((target_< simd_< ints8_<A0>, boost::simd::tag::sse_ > >))
                            )
  {
    typedef typename A0::type result_type;

    template< class I0, class I1,class I2,class I3
            , class I4, class I5,class I6,class I7
            , class I8, class I9,class IA,class IB
            , class IC, class ID,class IE,class IF
            >  inline result_type
    operator()( I0 const& a0  , I1 const& a1  , I2 const& a2  , I3 const& a3
              , I4 const& a4  , I5 const& a5  , I6 const& a6  , I7 const& a7
              , I8 const& a8  , I9 const& a9  , IA const& a10 , IB const& a11
              , IC const& a12 , ID const& a13 , IE const& a14 , IF const& a15
              ) const
    {
      result_type
      that =  { _mm_setr_epi8 ( a0, a1 , a2, a3  , a4 , a5 , a6 , a7
                              , a8, a9, a10, a11 , a12, a13, a14, a15 )
              };
      return that;
    }
  };
} } }

#endif
#endif
