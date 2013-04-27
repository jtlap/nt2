//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_MEMORY_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/memory/functions/load.hpp>
#include <boost/simd/include/functions/simd/unaligned_load.hpp>
#include <boost/simd/toolbox/memory/functions/details/check_ptr.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/mpl/if.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Regular SIMD load for double with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      (scalar_< integer_<A1> >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 a1, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 + a1, sizeof(result_type));
      return _mm256_load_pd(a0+a1);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for double without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_pd(a0);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for single with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      (scalar_< integer_<A1> >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 a1, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 + a1, sizeof(result_type));
      return _mm256_load_ps(a0+a1);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for single without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_ps(a0);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for integers with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)(A2)
                                    , (iterator_< scalar_< integer_<A0> > >)
                                      (scalar_< integer_<A1> >)
                                      ((target_ < simd_ < integer_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                            )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 a1, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 + a1, sizeof(result_type));
      return _mm256_load_si256(reinterpret_cast<__m256i const*>(a0+a1));
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for integers without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< integer_<A0> > >)
                                      ((target_ < simd_ < integer_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                            )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_si256(reinterpret_cast<__m256i const*>(a0));
    }
  };

  /// INTERNAL ONLY - Misaligned load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)(A3)
                                    , (iterator_< scalar_< arithmetic_<A0> > >)
                                      ((target_ < simd_ < arithmetic_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A2::type result_type;

    static const std::size_t cardinal = meta::cardinal_of<result_type>::value;
    static const typename A3::value_type unalignment = A3::value % cardinal;

    typedef typename boost::mpl::if_c < unalignment
                                      , boost::simd::tag::unaligned_load_
                                      , boost::simd::tag::load_
                                      >::type           func_t;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2& a2, const A3&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 - A3::value, sizeof(result_type));
      typename boost::dispatch::make_functor<func_t, A0>::type callee;
      return callee( a0, a2 );
    }
  };
} } }

#endif
#endif
