/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_IS_SET_HPP_INCLUDED
#define NT2_SDK_META_IS_SET_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Lightweight checking if T is a static types set
// See: http://nt2.metascale.org/sdk/meta/set/is_set.hpp
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace meta
{
  template<class T, class V = void>
  struct is_set : boost::mpl::false_ {};

  template<class T>
  struct is_set<T, typename T::is_set_type> : boost::mpl::true_ {};
} }

#endif
