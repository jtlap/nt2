//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_INDICES_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the ind2ind function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct indices_ : ext::generative_<indices_>
    {
      typedef ext::generative_<indices_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::indices_, indices, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::indices_, indices, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::indices_, indices, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::indices_, indices, 4)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::indices_, indices, 5)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::indices_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::indices_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
