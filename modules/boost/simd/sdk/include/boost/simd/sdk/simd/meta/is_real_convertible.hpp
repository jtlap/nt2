/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_REAL_CONVERTIBLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_REAL_CONVERTIBLE_HPP_INCLUDED

#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct  is_real_convertible
        : boost::mpl::bool_  <  (    sizeof(float)
                              <=  sizeof(typename boost::dispatch::meta::scalar_of<T>::type)
                              )
                            > {};
} } }

#endif
