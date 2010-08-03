/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_DETAILS_CARDINAL_OF_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_DETAILS_CARDINAL_OF_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace details
{
  ////////////////////////////////////////////////////////////////////////////
  // Overload for SIMD native types
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class C, class X>
  struct cardinal_of_impl<T,tag::simd_(C,X)> : boost::mpl::int_<T::static_size> {};
} }

#endif

