/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_RIC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RIC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct ric_ : ext::generative_<ric_>
    {
      typedef ext::generative_<ric_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, ric, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, ric, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, ric, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, C_rows, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, C_rows, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ric_, C_rows, 3)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::ric_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::ric_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
