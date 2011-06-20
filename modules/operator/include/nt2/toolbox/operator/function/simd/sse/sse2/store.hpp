//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_STORE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// store for SIMD types
// TODO : Documentation for simd store
// TODO : Make them work properly with ContiguousRandomAccessIterator
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over store for double SIMD types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::store_
                      , tag::cpu_
                      
                            , (A0)(A1)(A2)
                            , ((simd_< double_<A0>, tag::sse_ >))(iterator_< double_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_pd(a1+2*a2,a0);
      return a0;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over store for float SIMD types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::store_
                      , tag::cpu_
                      
                            , (A0)(A1)(A2)
                            , ((simd_< float_<A0>, tag::sse_ >))(iterator_< float_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_ps(a1+4*a2,a0);
      return a0;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over store for integral SIMD types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::store_
                      , tag::cpu_
                      
                            , (A0)(A1)(A2)
                            , ((simd_< integer_<A0>, tag::sse_ >))(iterator_< integer_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      _mm_store_si128((__m128i*)(a1)+a2, a0);
      return a0;
    }
  };
} }


#endif
