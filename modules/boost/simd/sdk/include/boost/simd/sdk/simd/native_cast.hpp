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

#include <boost/mpl/and.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/simd/sdk/details/bitwise_cast.hpp>

namespace boost { namespace simd
{
  template<class T,class U> inline
  typename boost::enable_if_c <     meta::is_native<T>::value
                                &&  meta::is_native<U>::value
                              , T
                              >::type
  native_cast( U const& a )
  {
    typedef typename T::native_type native_type;
    T that = { bitwise_cast<native_type>(a.data_) };
    return that;
  }

  template<class T,class U> inline
  typename boost::enable_if_c <     meta::is_native<T>::value
                                &&  meta::is_simd_specific< U
                                                          , typename
                                                            T::extension_type
                                                          >::value
                              , T
                              >::type
  native_cast( U const& a )
  {
    typedef typename T::native_type native_type;
    T that = { bitwise_cast<native_type>(a) };
    return that;
  }
} }

#endif
