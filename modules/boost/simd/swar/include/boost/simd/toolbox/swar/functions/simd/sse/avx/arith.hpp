//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_ARITH_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_ARITH_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/arith.hpp>
#include <boost/simd/include/functions/make.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ < double_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      result_type that = { _mm256_set_pd(3.0,2.0,1.0,0.0) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ <  single_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      result_type that = {_mm256_set_ps(7.0f,6.0f,5.0f,4.0f,3.0f,2.0f,1.0f,0.0f)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ < ints64_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      return bitwise_cast<result_type>(_mm256_set_epi32(0,3,0,2,0,1,0,0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ < ints32_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      result_type that = {_mm256_set_epi32(7,6,5,4,3,2,1,0)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ < ints16_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      result_type that = { _mm256_set_epi16( 15, 14, 13, 12, 11, 10, 9, 8
                                           , 7,  6,  5,  4,  3,  2,  1, 0
                                           )
                         };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::arith_
                                    , boost::simd::tag::avx_
                                    , (T)
                                    , ((target_ < simd_ < ints8_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(T const&) const
    {
      result_type that = { _mm256_set_epi8( 31, 30, 29, 28, 27, 26, 25, 24
                                          , 23, 22, 21, 20, 19, 18, 17, 16
                                          , 15, 14, 13, 12, 11, 10, 9,  8
                                          , 7,  6,  5,  4,  3,  2,  1,  0
                                          )
                         };
      return that;
    }
  };

} } }

#endif
#endif
