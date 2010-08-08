/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_META_IS_NATIVE_HPP_INCLUDED
#define NT2_SDK_SIMD_META_IS_NATIVE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/simd/native.hpp>

namespace nt2 { namespace meta
{
  template<class T> struct is_native : boost::mpl::false_ {};

  template<class T, class X>
  struct is_native<nt2::simd::native<T,X> >: boost::mpl::true_ {};
} }

#endif
