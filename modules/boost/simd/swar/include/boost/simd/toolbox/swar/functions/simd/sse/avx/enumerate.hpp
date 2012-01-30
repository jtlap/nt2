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
} } }

#endif
#endif
