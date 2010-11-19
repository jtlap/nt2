/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_OFFSET_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_OFFSET_HPP_INCLUDED

#include <nt2/sdk/simd/meta/as_simd.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // load dispatch type for offset SIMD load
  //////////////////////////////////////////////////////////////////////////////
  template< int N
          , std::size_t Card
          , bool isPeriodic = (N % Card == 0)
          , bool isForward  = (N>=0)
          >
  struct load_status
  {
    BOOST_STATIC_CONSTANT(std::size_t   , bytes   = 16/Card             );
    BOOST_STATIC_CONSTANT(std::ptrdiff_t, offset  = N/Card              );
    BOOST_STATIC_CONSTANT(std::ptrdiff_t, shifta  = bytes*(N%Card)      );
    BOOST_STATIC_CONSTANT(std::ptrdiff_t, shiftb  = bytes*(Card-N%Card) );
  };
} }

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // When in SIMD, load dispatch on T scalar value and Offset quality
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset,class C, class X, class Info>
  struct  dispatch<load_<T,Offset>,tag::simd_(C,X),Info>
        : boost::mpl
          ::always< details::load_status< Offset
                                        , meta::cardinal_of<T>::value
                                        >
                  >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // load with offset  -- Periodic offset
  // Offset is a multiple of type cardinal so we just do a load with a full
  // number of vector offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset, std::size_t Card, class Info, bool Fwd>
  struct  call< load_<T,Offset>
              , tag::simd_(tag::arithmetic_,tag::sse_)
              , details::load_status<Offset,Card,true,Fwd> , Info
              >
        : callable
  {
    typedef T result_type;
    typedef details::load_status<Offset,Card,true,Fwd> status_type;

    NT2_FUNCTOR_CALL(2)
    {
      return load<T>(a0,a1+status_type::offset);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // load with offset  -- Forward, Non-Periodic offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset, std::size_t Card, class Info>
  struct  call< load_<T,Offset>
              , tag::simd_(tag::arithmetic_,tag::sse_)
              , details::load_status<Offset,Card,false,true> , Info
              >
        : callable
  {
    typedef T                                                         result_type;
    typedef details::load_status<Offset,Card,false,true>              status_;
    typedef typename meta::as_simd< typename meta::scalar_of<T>::type
                                  , tag::sse_
                                  >::type                             raw_type;

    NT2_FUNCTOR_CALL(2)
    {
      T a     = load<T>(a0,a1+status_::offset);
      T b     = load<T>(a0,a1+status_::offset+1);
      T sa    = { (raw_type)_mm_srli_si128((__m128i)(a.data_),status_::shifta) };
      T sb    = { (raw_type)_mm_slli_si128((__m128i)(b.data_),status_::shiftb) };
      T that  = { sa | sb };
      return that;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // load with offset  -- Backward, Non-Periodic offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,int Offset, std::size_t Card, class Info>
  struct  call< load_<T,Offset>
              , tag::simd_(tag::arithmetic_,tag::sse_)
              , details::load_status<Offset,Card,false,false> , Info
              >
        : callable
  {
    typedef T                                                         result_type;
    typedef details::load_status<-Offset,Card>                        status_;
    typedef typename meta::as_simd< typename meta::scalar_of<T>::type
                                  , tag::sse_
                                  >::type                             raw_type;

    NT2_FUNCTOR_CALL(2)
    {
      T a     = load<T>(a0,a1-status_::offset);
      T b     = load<T>(a0,a1-status_::offset-1);
      T sa    = { (raw_type)_mm_slli_si128((__m128i)(a.data_),status_::shifta) };
      T sb    = { (raw_type)_mm_srli_si128((__m128i)(b.data_),status_::shiftb) };
      T that  = { sa | sb };
      return that;
    }
  };
} }

#endif
