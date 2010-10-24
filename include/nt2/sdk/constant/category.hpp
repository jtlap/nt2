/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Category for constants
//* TODO:  Documentation: http://nt2.lri.fr/sdk/constant/meta/category.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>
#include <nt2/sdk/functor/meta/belong_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// constant_ wraps a constant type into a EDSL element
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace constants
{
  template<class Cst> struct constant_ { typedef Cst type; };
} }

namespace nt2 { namespace tag
{
  struct constant_ {};
} }

namespace nt2 { namespace functors
{
  template<class T>
  struct  constant_ : nt2::tag::category<constant_<T>,0x10000000,0>
  {
    typedef typename meta::category_of<T>::type::tag base_category;
    typedef nt2::tag::constant_ tag(base_category);
  };
} }

namespace nt2 { namespace meta
{
  template<class T> struct category_of< as_<T> > : functors::constant_<T> {};

  template<class T>
  struct  category_of< constants::constant_<T> > : category_of< as_<T> > {};

  template<class T, class S>
  struct  belong_to<as_<T>,S> : belong_to<T,S> {};
} }

#endif
