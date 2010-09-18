/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_DOWNGRADE_HPP_INCLUDED
#define NT2_SDK_META_DOWNGRADE_HPP_INCLUDED

#include <nt2/sdk/meta/sign_of.hpp>
#include <nt2/sdk/functor/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>
#include <nt2/sdk/meta/make_integer.hpp>

namespace nt2 { namespace details
{
  template<class T,std::size_t Size, class Sign, class Category>
  struct downgrade;

	//////////////////////////////////////////////////////////////////////////////
	// Scalar arithmetic types are downgraded using make_integer
	//////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, class Sign>
  struct 	downgrade<T,Size,Sign,tag::scalar_(tag::arithmetic_)>
				: meta::make_integer<Size/2,Sign>
	{};

	//////////////////////////////////////////////////////////////////////////////
	// If type size is 1, return the type itself for any category
	//////////////////////////////////////////////////////////////////////////////
  template<class T, class Sign>
  struct 	downgrade<T,1,Sign,tag::scalar_(tag::arithmetic_)>
				: meta::make_integer<1,Sign> {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any type, return the integer type of size equals to sizeof(T)/2
	// with an optional sign change
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Sign=typename meta::sign_of<T>::type>
  struct  downgrade
        : details::downgrade< T,sizeof(T),Sign
													  , typename category_of<T>::type::tag
														> {};

} }

#endif

