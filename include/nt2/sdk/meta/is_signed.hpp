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

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Sign is Ok for arithmetic types
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Hierarchy> struct is_signed : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // Sign has no meaning on other types most of the time
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct is_signed<T, meta::unspecified_<T> > : boost::mpl::false_ {};

  //////////////////////////////////////////////////////////////////////////////
  // ... unless they are unsigned of course
  //////////////////////////////////////////////////////////////////////////////
  template<class Hierarchy>
  struct is_signed<uint8_t ,Hierarchy>  : boost::mpl::false_ {};
  template<class Hierarchy>
  struct is_signed<uint16_t,Hierarchy>  : boost::mpl::false_ {};
  template<class Hierarchy>
  struct is_signed<uint32_t,Hierarchy>  : boost::mpl::false_ {};
  template<class Hierarchy>
  struct is_signed<uint64_t,Hierarchy>  : boost::mpl::false_ {};
  template<class Hierarchy>
  struct is_signed<bool    ,Hierarchy>  : boost::mpl::false_ {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Return true or false depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_signed
        : details::is_signed< typename strip<T>::type
                            , typename meta::hierarchy_of<T>::type>
  {};
  //////////////////////////////////////////////////////////////////////////////
  // Return false or true depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct is_unsigned : boost::mpl::not_< is_signed<T> >
  {};
} }

#endif
