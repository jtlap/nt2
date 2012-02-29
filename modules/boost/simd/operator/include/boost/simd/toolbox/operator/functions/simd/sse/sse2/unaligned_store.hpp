//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_UNALIGNED_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// unaligned_store for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// TODO : Documentation for simd unaligned_store
// TODO : Make them work properly with ContiguousRandomAccessIterator
//==============================================================================
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

//==============================================================================
// unaligned_store vector of double
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , ((simd_< double_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< double_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      _mm_storeu_pd(a1+a2,a0);
      return a0;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_< double_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< double_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      _mm_storeu_pd(a1,a0);
      return a0;
    }
  };
} } }

//==============================================================================
// unaligned_store vector of float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< single_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      _mm_storeu_ps(a1+a2,a0);
      return a0;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< single_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      _mm_storeu_ps(a1,a0);
      return a0;
    }
  };
} } }

//==============================================================================
// unaligned_store vector of integer
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)(A2)
                            , ((simd_< integer_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< integer_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      _mm_storeu_si128(reinterpret_cast<__m128i*>(a1+a2), a0);
      return a0;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_< integer_<A0>, boost::simd::tag::sse_ >))
                              (iterator_< scalar_< integer_<A1> > >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      _mm_storeu_si128(reinterpret_cast<__m128i*>(a1), a0);
      return a0;
    }
  };
} } }

#endif
#endif
