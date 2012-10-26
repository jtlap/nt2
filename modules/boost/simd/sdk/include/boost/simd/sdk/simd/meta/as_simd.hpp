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
  {
    typedef boost::simd::memory::aligned_array<T, N / sizeof(T), boost::simd::memory::max_alignment<N>::value> type;
  };

} } }

#endif
