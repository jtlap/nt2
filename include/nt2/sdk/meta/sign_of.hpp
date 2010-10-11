/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_SIGN_OF_HPP_INCLUDED
#define NT2_SDK_META_SIGN_OF_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Sign has no meanign on types most of the time
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Category> struct sign_of { typedef unsigned type; };

  //////////////////////////////////////////////////////////////////////////////
  // Except for arithmetic types
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct sign_of<T,tag::scalar_(tag::arithmetic_)> {  typedef signed type; };

  //////////////////////////////////////////////////////////////////////////////
  // ... unless they are unsigned of course
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct sign_of<uint8_t ,tag::scalar_(tag::arithmetic_)> { typedef unsigned type; };
  template<>
  struct sign_of<uint16_t,tag::scalar_(tag::arithmetic_)> { typedef unsigned type; };
  template<>
  struct sign_of<uint32_t,tag::scalar_(tag::arithmetic_)> { typedef unsigned type; };
  template<>
  struct sign_of<uint64_t,tag::scalar_(tag::arithmetic_)> { typedef unsigned type; };
  template<>
  struct sign_of<bool    ,tag::scalar_(tag::arithmetic_)> { typedef unsigned type; };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Return trues or false depending on T is signed or not
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  sign_of
        : details::sign_of< typename strip<T>::type
                          , typename meta::category_of<T>::type::tag
                          >
  {};
} }


#endif
