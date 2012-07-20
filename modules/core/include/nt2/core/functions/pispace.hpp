//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_PISPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_PISPACE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct pispace_ : ext::generative_<pispace_>
    {
      typedef ext::generative_<pispace_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::pispace_, pispace, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::pispace_, pispace, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::pispace_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::pispace_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
