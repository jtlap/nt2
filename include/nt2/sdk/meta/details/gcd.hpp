/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_DETAILS_GCD_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_GCD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Implementation details of gcd
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/int.hpp>

namespace nt2 { namespace details
{
  template<int A, int B, bool BIsNull = (B == 0)>
  struct gcd_impl;

  template<int A, int B>
  struct  gcd_impl<A,B,true> : boost::mpl::int_<A> {};

  template<int A, int B>
  struct  gcd_impl<A,B,false> : boost::mpl::int_<gcd_impl<B,A%B>::value> {};
} }

#endif
