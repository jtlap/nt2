/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_AS_INTEGER_HPP_INCLUDED
#define NT2_SDK_META_AS_INTEGER_HPP_INCLUDED

#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/meta/category_of.hpp>
#include <nt2/sdk/meta/make_integer.hpp>

namespace nt2 { namespace details
{
  template<class T, class Sign, class Category> struct as_integer;

  template<class T, class Sign>
  struct 	as_integer<T,Sign,tag::scalar_(tag::arithmetic_)>
				: meta::make_integer<sizeof(T),Sign> {};
	
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Turn any type into its integral equivalent
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign=typename meta::sign_of<T>::type >
  struct  as_integer
        : details::as_integer<T,Sign,typename category_of<T>::type::tag > {};
} }

#endif

