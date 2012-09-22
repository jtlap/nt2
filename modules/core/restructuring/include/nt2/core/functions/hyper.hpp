//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HYPER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HYPER_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the hyper function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the hyper functor
    **/
    struct hyper_ : ext::elementwise_<hyper_>
    {
      typedef ext::elementwise_<hyper_> parent;
    };
  }

  /*!
    @brief Hyperplane extraction

    Returns the hyperplane of index i along the selected direction.
    By default n is the first non-singleton dimension of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::hyper_       , hyper, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::hyper_       , hyper, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::hyper_       , hyper, 3)
}

namespace nt2 { namespace ext
{
  //TODO Refurbish later when expression node is correct
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::hyper_,Domain,N,Expr>
        : meta::boxed_size<Expr,5>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::hyper_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
