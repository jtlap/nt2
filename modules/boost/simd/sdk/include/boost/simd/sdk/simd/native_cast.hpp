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
#include <boost/simd/sdk/details/bitwise_cast.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd
{
  template<class T> BOOST_DISPATCH_FORCE_INLINE
  typename boost::enable_if_c<meta::is_native<T>::value, T const&>::type
  native_cast( T const& a )
  {
    return a;
  }

  template<class T,class U> BOOST_DISPATCH_FORCE_INLINE
  typename boost::enable_if_c<meta::is_native<T>::value, T const&>::type
  native_cast( typename T::native_type const& a )
  {
    return reinterpret_cast<T const&>(a);
  }

#ifdef BOOST_SIMD_NO_STRICT_ALIASING
  #define M0 T const&
  #define M1(t) return reinterpret_cast<T const&>(t);
#else
  #define M0 T
  #define M1(t)                                                               \
  typedef typename T::native_type native_type;                                \
  T that = { bitwise_cast<native_type>(t) };                                  \
  return that;                                                                \
  /**/
#endif

  template<class T,class U> BOOST_DISPATCH_FORCE_INLINE
  typename boost::enable_if_c <     meta::is_native<T>::value
                                &&  meta::is_native<U>::value
                                && !is_same<T,U>::value
                              , M0
                              >::type
  native_cast( U const& a )
  {
    M1(a.data_);
  }

  template<class T,class U> BOOST_DISPATCH_FORCE_INLINE
  typename boost::enable_if_c <     meta::is_native<T>::value
                                &&  meta::is_simd_specific< U
                                                          , typename
                                                            T::extension_type
                                                          >::value
                              , M0
                              >::type
  native_cast( U const& a )
  {
    M1(a);
  }

#undef M1
#undef M0

} }

#endif
