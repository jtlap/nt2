/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_CAST_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_CAST_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd
{
  template<class T, class U>
  BOOST_DISPATCH_FORCE_INLINE
  T const&
  native_cast( U const& a )
  {
    return reinterpret_cast<T const&>(a);
  }

} }

#endif
