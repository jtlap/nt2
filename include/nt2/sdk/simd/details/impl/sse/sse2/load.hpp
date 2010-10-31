/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // load with no offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Info>
  struct  call< load_<T,0>  , tag::simd_(tag::arithmetic_,tag::sse_)
              , fundamental_, Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL_DISPATCH (   2, typename meta::scalar_of<T>::type
                              , ( 3, (double,float,integer_) )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double   )
    {
      T that = { _mm_load_pd(a0+a1*meta::cardinal_of<T>::value) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float    )
    {
      T that = { _mm_load_ps(a0+a1*meta::cardinal_of<T>::value) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,integer_ )
    {
      result_type that = { _mm_load_si128(reinterpret_cast<__m128i const*>(a0)+a1) };
      return that;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // load with a scalar offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T, int Offset,class Info>
  struct  call< load_<T,Offset> , tag::simd_(tag::arithmetic_,tag::sse_)
              , fundamental_    , Info
              >
        : callable

  {
    BOOST_STATIC_CONSTANT(std::size_t, card = meta::cardinal_of<T>::value );
    typedef T result_type;

    ////////////////////////////////////////////////////////////////////////////
    // Internal offset based load generation
    ////////////////////////////////////////////////////////////////////////////
    template< int N
            , bool isPeriodic = (N % card == 0)
            , bool isForward = (N>=0)
            >
    struct loader_;

    ////////////////////////////////////////////////////////////////////////////
    // Main operator()()
    ////////////////////////////////////////////////////////////////////////////
    NT2_FUNCTOR_CALL(2)
    {
      loader_<Offset> callee;
      return callee(a0,a1);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Offset is a multiple of type cardinal so we just do a load with a full
    // number of vector offset
    ////////////////////////////////////////////////////////////////////////////
    template<int N,bool isForward> struct loader_<N,true,isForward>
    {
      typedef T result_type;

      template<class A0,class A1> inline
      result_type operator()(A0 const& a0, A1 const& a1 ) const
      {
        BOOST_STATIC_CONSTANT(std::ptrdiff_t, shift_fwd = N/card );
        return load<T>(a0,a1+shift_fwd);
      }
    };

    ////////////////////////////////////////////////////////////////////////////
    // Offset is a fragment of vector cardinal and goes forward
    // TODO: Refactor using | and sli/sri
    ////////////////////////////////////////////////////////////////////////////
    template<int N> struct loader_<N,false,true>
    {
      BOOST_STATIC_CONSTANT(std::size_t   , card    = meta::cardinal_of<T>::value );
      BOOST_STATIC_CONSTANT(std::size_t   , bytes   = 16/card                     );
      BOOST_STATIC_CONSTANT(std::ptrdiff_t, offset  = N/card                      );
      BOOST_STATIC_CONSTANT(std::ptrdiff_t, shifta  = bytes*(N%card)              );
      BOOST_STATIC_CONSTANT(std::ptrdiff_t, shiftb  = bytes*(card-N%card)         );

      typedef T result_type;

      NT2_FUNCTOR_DISPATCH( 2 , typename meta::scalar_of<T>::type
                          , ( 3, (double,float,integer_) ), loader_
                          )

      NT2_FUNCTOR_EVAL_IF(2,double, loader_)
      {
        T a     = load<T>(a0,a1+offset);
        T b     = load<T>(a0,a1+offset+1);
        T that  = { _mm_or_pd ( (__m128d)_mm_srli_si128((__m128i)(a.data_),shifta)
                              , (__m128d)_mm_slli_si128((__m128i)(b.data_),shiftb)
                              )
                  };
        return that;
      }

      NT2_FUNCTOR_EVAL_IF(2,float, loader_)
      {
        T a     = load<T>(a0,a1+offset);
        T b     = load<T>(a0,a1+offset+1);
        T that  = { _mm_or_ps ( (__m128)_mm_srli_si128((__m128i)(a.data_),shifta)
                              , (__m128)_mm_slli_si128((__m128i)(b.data_),shiftb)
                              )
                  };
        return that;
      }

      NT2_FUNCTOR_EVAL_IF(2,integer_, loader_)
      {
        T a     = load<T>(a0,a1+offset);
        T b     = load<T>(a0,a1+offset+1);
        T that  = { _mm_or_si128( _mm_srli_si128(a,shifta)
                                , _mm_slli_si128(b,shiftb)
                                )
                  };
        return that;
      }
    };

    ////////////////////////////////////////////////////////////////////////////
    // Offset is a fragment of vector cardinal and goes backward
    ////////////////////////////////////////////////////////////////////////////
    template<int N> struct loader_<N,false,false>
    {
      BOOST_STATIC_CONSTANT(std::size_t   , card    = loader_<-N>::card   );
      BOOST_STATIC_CONSTANT(std::size_t   , bytes   = loader_<-N>::byte   );
      BOOST_STATIC_CONSTANT(std::ptrdiff_t, offset  = loader_<-N>::offset );
      BOOST_STATIC_CONSTANT(uint8_t       , shifta  = loader_<-N>::shifta );
      BOOST_STATIC_CONSTANT(uint8_t       , shiftb  = loader_<-N>::shiftb );

      typedef T result_type;

      NT2_FUNCTOR_DISPATCH( 2, typename meta::scalar_of<T>::type
                          , ( 3, (double,float,integer_) ), loader_
                          )

      NT2_FUNCTOR_EVAL_IF(2,double, loader_)
      {
        T a     = load<T>(a0,a1-offset);
        T b     = load<T>(a0,a1-(offset+1));
        T that  = { _mm_or_pd ( (__m128d)_mm_slli_si128((__m128i)(a.data_),shifta)
                              , (__m128d)_mm_srli_si128((__m128i)(b.data_),shiftb)
                              )
                  };
        return that;
      }

      NT2_FUNCTOR_EVAL_IF(2,float, loader_)
      {
        T a     = load<T>(a0,a1+offset);
        T b     = load<T>(a0,a1+offset-1);
        T that  = { _mm_or_ps ( (__m128)_mm_slli_si128((__m128i)(a.data_),shifta)
                              , (__m128)_mm_srli_si128((__m128i)(b.data_),shiftb)
                              )
                  };
        return that;
      }

      NT2_FUNCTOR_EVAL_IF(2,integer_, loader_)
      {
        T a     = load<T>(a0,a1+offset);
        T b     = load<T>(a0,a1+offset-1);
        T that  = { _mm_or_si128( _mm_slli_si128(a,shifta)
                                , _mm_srli_si128(b,shiftb)
                                )
                  };
        return that;
      }
    };
  };
} }


#endif
