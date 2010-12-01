/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_CATEGORY_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Basic category registration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

////////////////////////////////////////////////////////////////////////////////
// Use this macro to put a type in the scalar familly
////////////////////////////////////////////////////////////////////////////////
#define NT2_CATEGORY_SCALAR_FAMILY 1

////////////////////////////////////////////////////////////////////////////////
// Family tags for call/validate writings
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct scalar_      {};
  struct arithmetic_;
} }

////////////////////////////////////////////////////////////////////////////////
// scalar_ metafunction for building a category
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class T, std::size_t R>
  struct  scalar_
        : nt2::tag::category<scalar_<T,R>,NT2_CATEGORY_SCALAR_FAMILY,R>
  {
    typedef nt2::tag::scalar_ tag(T);
  };
} }

#endif
