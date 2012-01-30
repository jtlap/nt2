//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_ENUMERATE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/enumerate.hpp>
#include <boost/simd/include/functions/make.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ < double_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that = { _mm256_set_pd(a0+3,a0+2,a0+1,a0) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ <  single_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that = {_mm256_set_ps(a0+7,a0+6,a0+5,a0+4,a0+3,a0+2,a0+1,a0)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ < ints64_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      return make<result_type>(a0, a0+1, a0+2, a0+3) };
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ < ints32_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that = {_mm256_set_epi32(a0+7,a0+6,a0+5,a0+4,a0+3,a0+2,a0+1,a0)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ < ints16_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that = { _mm256_set_epi16( a0+15, a0+14, a0+13, a0+12, a0+11, a0+10, a0+9, a0+8
                                           , a0+7,  a0+6,  a0+5,  a0+4,  a0+3,  a0+2,  a0+1, a0
                                           )
                         };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_
                                    , boost::simd::tag::avx_
                                    , (A0)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_ < simd_ < ints8_<T>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename T::type result_type;

    result_type operator()(A0 const& a0, T const& ) const
    {
      result_type that = { _mm256_set_epi8( a0+31, a0+30, a0+29, a0+28, a0+27, a0+26, a0+25, a0+24
                                          , a0+23, a0+22, a0+21, a0+20, a0+19, a0+18, a0+17, a+16
                                          , a0+15, a0+14, a0+13, a0+12, a0+11, a0+10, a0+9,  a0+8
                                          , a0+7,  a0+6,  a0+5,  a0+4,  a0+3,  a0+2,  a0+1,  a0
                                          )
                         };
      return that;
    }
  };
} } }

#endif
#endif
