//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_AS_INDEX_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_AS_INDEX_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct as_index
  {
    typedef std::size_t type;
  };

  template<class T, class X>
  struct as_index< boost::simd::native<T, X> >
  {
    typedef typename meta::as_arithmetic<T>::type arith;
    typedef typename dispatch::meta::as_integer<arith, unsigned>::type integer;
    typedef boost::simd::native<integer, X> type;
  };
} } }

#endif
