/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_THROUGH_VOLATILE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_THROUGH_VOLATILE_HPP_INCLUDED

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Pass some value through volatile state to prevent eager optimizations
  template<class T> T through_volatile(T const& t)
  {
    return const_cast<T const&>(const_cast<T const volatile&>(t));
  }
} }

#endif
