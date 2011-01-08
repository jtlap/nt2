/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_UPGRADE_HPP_INCLUDED
#define NT2_SDK_META_UPGRADE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/make_integer.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Scalar arithmetic types are upgraded using make_integer
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, class Sign, class Hierarchy>
  struct upgrade : meta::make_integer<Size*2,Sign> {};

  //////////////////////////////////////////////////////////////////////////////
  // Other type are idempotent
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, class Sign>
  struct upgrade<T,Size,Sign,meta::unknown_<T> > { typedef T type; };

  //////////////////////////////////////////////////////////////////////////////
  // If type size is 8, return the type itself for any category
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Sign, class Hierarchy>
  struct   upgrade<T,8,Sign,Hierarchy>
        : meta::make_integer<8,Sign> {};


  template<class Sign, class Hierarchy>
  struct upgrade<double,sizeof(double),Sign,Hierarchy>
  {
    typedef double type;
  };

  template<class Sign, class Hierarchy>
  struct upgrade<float,sizeof(float),Sign,Hierarchy>
  {
    typedef double type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any type, return the integer type of size equals to sizeof(T)*2
  // with an optional sign change
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign=typename meta::sign_of<T>::type>
  struct  upgrade
        : details::upgrade< typename strip<T>::type
                          , sizeof(T),Sign
                          , typename hierarchy_of<T>::type
                          > {};

} }

#endif

