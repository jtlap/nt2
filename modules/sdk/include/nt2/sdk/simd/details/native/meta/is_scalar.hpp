/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_META_IS_SCALAR_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_META_IS_SCALAR_HPP_INCLUDED

#include <nt2/sdk/meta/is_scalar.hpp>

namespace nt2 { namespace details
{
  template<class T,class X>
  struct is_scalar< meta::simd_<T,X> >  : boost::mpl::false_ {};
} }

#endif
