//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_ALL_REDUCE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/all_reduce.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::avx_
                                    , (Tag)(A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      return eval(a0, dispatch::functor<base>());
    }

    BOOST_FORCEINLINE
    result_type eval(__m256d a0, dispatch::functor<base> const& op) const
    {
      A0          xs    = _mm256_permute_pd(a0, _MM_SHUFFLE2(2,1) );
      result_type that  = op( xs
                            , bitwise_cast<A0>(_mm256_permute2f128_pd(xs,xs,1))
                            );
      result_type pthat = _mm256_permute_pd(that, _MM_SHUFFLE2(2,1));

      return op(that,pthat);
    }

    BOOST_FORCEINLINE
    result_type eval(__m256i a0, dispatch::functor<base> const& op) const
    {
      __m256d     xs    = _mm256_permute_pd(__m256d(a0), _MM_SHUFFLE2(2,1));
      result_type that  = op( bitwise_cast<A0>(xs)
                            , bitwise_cast<A0>(_mm256_permute2f128_pd(xs,xs,1))
                            );

      return op ( that
                , bitwise_cast<result_type>
                          ( _mm256_permute_pd ( bitwise_cast<__m256d>(that)
                                              , _MM_SHUFFLE2(2,1)
                                              )
                          )
                );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::avx_
                                    , (Tag)(A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      return eval(a0, dispatch::functor<base>());
    }

    BOOST_FORCEINLINE
    result_type eval(__m256 a0, dispatch::functor<base> const& op) const
    {
      A0          xs    = _mm256_permute_ps(a0, _MM_SHUFFLE( 0,3,2,1 ) );
      result_type that  = op( xs
                            , bitwise_cast<A0>(_mm256_permute2f128_ps(xs,xs,1))
                            );
      result_type pthat = _mm256_permute_ps(that, _MM_SHUFFLE( 1,0,3,2 ));

      that  = op(that,pthat);
      pthat = _mm256_permute_ps(that,_MM_SHUFFLE(2,3,0,1));

      return op(that,pthat);
    }

    BOOST_FORCEINLINE
    result_type eval(__m256i a0, dispatch::functor<base> const& op) const
    {
      __m256      xs    = _mm256_permute_ps(__m256(a0),_MM_SHUFFLE(0,3,2,1));
      result_type that  = op( bitwise_cast<A0>(xs)
                            , bitwise_cast<A0>(_mm256_permute2f128_ps(xs,xs,1))
                            );
      result_type pthat = bitwise_cast<result_type>
                          ( _mm256_permute_ps ( bitwise_cast<__m256>(that)
                                              , _MM_SHUFFLE( 1,0,3,2 )
                                              )
                          );

      that  = op(that,pthat);
      pthat = bitwise_cast<result_type>
              ( _mm256_permute_ps ( bitwise_cast<__m256>(that)
                                  , _MM_SHUFFLE( 2,3,0,1 )
                                  )
              );

      return op(that,pthat);
    }
  };
} } }

#endif
#endif
