/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_META_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_AS_SIMD_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/sdk/memory/aligned_array_fwd.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>
#include <boost/simd/sdk/config/types.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

namespace boost { namespace simd { namespace meta
{
  template<class T, class Extension, class Enable = void>
  struct as_simd
  {
    typedef dispatch::meta::na_ type;
  };

  template<std::size_t N, class T>
  struct as_simd<T, tag::simd_emulation_<N>, typename enable_if< is_fundamental<T> >::type>
  {
    typedef boost::simd::memory::aligned_array<T, N / sizeof(T), boost::simd::memory::max_alignment<N>::value> type;
  };

  template<std::size_t N, class T>
  struct as_simd<logical<T>, tag::simd_emulation_<N> >
       : as_simd<T, tag::simd_emulation_<N> >
  {
  };

  // Some GCC and Clang versions require full specializations
  #define M0(r,n,t)                                                            \
  template<>                                                                   \
  struct as_simd<t, tag::simd_emulation_<n> >                                  \
  {                                                                            \
    typedef t type __attribute__((__vector_size__(n)));                        \
  };                                                                           \
  /**/
  #define M1(z,n,t) BOOST_PP_SEQ_FOR_EACH(M0, n, BOOST_SIMD_TYPES)
#ifdef __GNUC__
  M0(0, 1, boost::simd::int8_t)
  M0(0, 1, boost::simd::uint8_t)
  M0(0, 2, boost::simd::int8_t)
  M0(0, 2, boost::simd::uint8_t)
  M0(0, 2, boost::simd::int16_t)
  M0(0, 2, boost::simd::uint16_t)
  M0(0, 4, boost::simd::int8_t)
  M0(0, 4, boost::simd::uint8_t)
  M0(0, 4, boost::simd::int16_t)
  M0(0, 4, boost::simd::uint16_t)
  M0(0, 4, boost::simd::int32_t)
  M0(0, 4, boost::simd::uint32_t)
  M0(0, 4, float)
  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(8, M1, ~)
#endif
  #undef M0
  #undef M1

} } }

#endif
