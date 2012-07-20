//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EYE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EYE_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the eye function
**/

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generative.hpp>
#include <nt2/sdk/meta/generative_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the eye functor
    **/
    struct eye_ : ext::generative_<eye_>
    {
      typedef ext::generative_<eye_> parent;
    };
  }

  /*!
    @brief Generate an identity matrix

    @param
    @param
    @param
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::eye_, eye, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::eye_, eye, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::eye_, eye, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  value_type<tag::eye_,Domain,N,Expr>
        : meta::generative_value<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<tag::eye_,Domain,N,Expr>
        : meta::generative_size<Expr>
  {};
} }

#endif
