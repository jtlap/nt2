//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIU_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::triu function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct triu_ : ext::elementwise_<triu_>
    {
      typedef ext::elementwise_<triu_> parent;
    };

    struct offset_triu_ : ext::elementwise_<offset_triu_>
    {
      typedef ext::elementwise_<offset_triu_>  parent;
    };
  }

  //============================================================================
  /*!
   * Upper triangular part of a 2D table.
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::triu_       , triu, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_triu_, triu, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct  value_type<nt2::tag::triu_,Domain,1,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr>
  struct  value_type<nt2::tag::offset_triu_,Domain,2,Expr>
        : meta::value_as<Expr,0>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::triu_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::offset_triu_,Domain,2,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
