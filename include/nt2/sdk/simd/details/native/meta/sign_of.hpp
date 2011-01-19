/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_META_SIGN_OF_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_META_SIGN_OF_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/is_signed.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Except for SIMD types
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class H, class X>
  struct  is_signed<T,meta::simd_<H,X> >
        : meta::is_signed<typename T::value_type>  {};
} }

#endif
