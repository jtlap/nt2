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
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Sign has no meanign on types most of the time
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Category> struct is_signed : boost::mpl::false_ {};

  //////////////////////////////////////////////////////////////////////////////
  // Except for arithmetic types
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct is_signed<T,tag::scalar_(tag::arithmetic_)>  : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // ... unless they are unsigned of course
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct is_signed<unsigned char ,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
  template<>
  struct is_signed<unsigned short,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
  template<>
  struct is_signed<unsigned int,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
  template<>
  struct is_signed<unsigned long,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
  template<>
  struct is_signed<unsigned long long,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
  template<>
  struct is_signed<bool    ,tag::scalar_(tag::arithmetic_)>  : boost::mpl::false_ {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Return true or false depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_signed
        : details::is_signed< typename strip<T>::type
                            , typename meta::category_of<T>::type::tag>
  {};
  //////////////////////////////////////////////////////////////////////////////
  // Return false or true depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_unsigned
    : boost::mpl::not_ < details::is_signed< typename strip<T>::type
                            , typename meta::category_of<T>::type::tag> > 
  {};
} }


#endif
