/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main generic constant class
//* TODO:  Documentation: http://nt2.lri.fr/sdk/constant/entity/constant.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/constant/category.hpp>

namespace nt2 { namespace functors
{
  template<class Tag,class Category,class Info>
  struct  dispatch<Tag,tag::constant_(Category),Info>
  {
    template<class T> struct apply                 : meta::scalar_of<T> {};
    template<class T> struct apply< meta::as_<T> > : meta::scalar_of<T> {};
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Generate a constant function as Name<Type>()
////////////////////////////////////////////////////////////////////////////////
#define NT2_CONSTANT_IMPLEMENTATION(TAG,NAME)                       \
template<class Target> inline                                       \
typename nt2::meta::enable_call<TAG(nt2::meta::as_<Target>)>::type  \
NAME()                                                              \
{                                                                   \
  nt2::functors::functor<TAG> callee;                               \
  return callee( nt2::meta::as_<Target>() );                        \
}                                                                   \
/**/

#endif
