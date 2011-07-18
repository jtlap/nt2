//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_STORE_HPP_INCLUDED

//==============================================================================
// TODO : Documentation for simd store
// TODO : Make them work properly with ContiguousRandomAccessIterator
//==============================================================================
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , ((simd_< double_<A0>, tag::sse_ >))
                              (iterator_< scalar_< double_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(3)
    {
      _mm_store_pd(a1+2*a2,a0);
      return a0;
    }
  };
} }

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , ((simd_< float_<A0>, tag::sse_ >))
                              (iterator_< scalar_< float_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(3)
    {
      _mm_store_ps(a1+4*a2,a0);
      return a0;
    }
  };
} }

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::store_ , tag::cpu_
                            , (A0)(A1)(A2)
                            , ((simd_< integer_<A0>, tag::sse_ >))
                              (iterator_< scalar_< integer_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(3)
    {
      _mm_store_si128((__m128i*)(a1)+a2, a0);
      return a0;
    }
  };
} }

#endif
