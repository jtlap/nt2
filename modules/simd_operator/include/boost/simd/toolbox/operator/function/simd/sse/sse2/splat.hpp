//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_SPLAT_HPP_INCLUDED

#include <boost/simd/sdk/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/details/ignore_unused.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/include/functions/make.hpp>

//==============================================================================
// Implementation when type A0 is double
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< double_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      result_type that = { _mm_set1_pd(a0)  };
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is float
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< float_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      result_type that = { _mm_set1_ps(a0)  };
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints8
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints8_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      result_type that = { _mm_set1_epi8(a0)  };
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints16
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints16_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      result_type that = { _mm_set1_epi16(a0)  };
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints32
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints32_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      result_type that = { _mm_set1_epi32(a0)  };
      return that;
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints64
//==============================================================================
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints64_<A1>, tag::sse_ > >))
                      )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      return make<typename A1::type>(a0, a0);
    }
  };
} } }

#endif
