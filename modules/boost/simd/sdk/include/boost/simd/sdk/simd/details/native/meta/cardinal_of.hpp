//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd { namespace ext
{
  ////////////////////////////////////////////////////////////////////////////
  // Overload for SIMD native types
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class H, class X>
  struct  cardinal_of_impl<T , dispatch::meta::simd_<H,X> >
        : boost::mpl::size_t<T::static_size> {};
} } }

#endif

