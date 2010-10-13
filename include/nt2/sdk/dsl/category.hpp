/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_CATEGORY_HPP_INCLUDED
#define NT2_SDK_DSL_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Basic category registration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Use this macro to put a type in the SIMD familly
////////////////////////////////////////////////////////////////////////////////
#define NT2_CATEGORY_AST_FAMILY 0x1000

////////////////////////////////////////////////////////////////////////////////
// Family tags for call/validate writings
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct ast_ {};
} }

////////////////////////////////////////////////////////////////////////////////
// ast_ metafunction for building an AST category
// Every proto expression have ast_(?) category, the ? depends on underlying
// elements and semantic.
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Base>
  struct  ast_ : nt2::tag::category<ast_<Base>,NT2_CATEGORY_AST_FAMILY,1>
  {
    typedef nt2::tag::ast_ tag(Base);
  };
} }

#endif
