/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_IS_SIGNED_HPP_INCLUDED
#define NT2_SDK_META_IS_SIGNED_HPP_INCLUDED

#include <boost/mpl/not.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Return true or false depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_signed
        : boost::is_base_of < meta::signed_<typename meta::primitive_of<T>::type>
                            , typename
                              meta::hierarchy_of<typename meta::primitive_of<T>::type>::type
                            >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Return false or true depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct is_unsigned : boost::mpl::not_< is_signed<T> >
  {};
} }

#endif
