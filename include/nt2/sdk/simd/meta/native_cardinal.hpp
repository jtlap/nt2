/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED
#define NT2_SDK_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <nt2/sdk/simd/extensions.hpp>

namespace nt2 { namespace meta
{
  template<class T>
  struct  native_cardinal
        : boost::mpl::size_t< NT2_SIMD_BYTES / sizeof(T) > {};
} }

#endif
