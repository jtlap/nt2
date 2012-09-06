//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::diag_of function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct diag_of_ : ext::elementwise_<diag_of_>
    {
      typedef ext::elementwise_<diag_of_> parent;
    };
    struct offset_diag_of_ : ext::elementwise_<offset_diag_of_>
    {
      typedef ext::elementwise_<offset_diag_of_>  parent;
    };
   }

  //============================================================================
  /*!
   * Extract the diagonal of a table as a vector
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diag_of_       , diag_of, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_diag_of_, diag_of, 2)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct generator<nt2::tag::diag_of_,Domain,N,Expr> : generate_as<Expr,0> {};

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::diag_of_,Domain,N,Expr> : boxed_size_of<Expr,2> {};

  template<class Domain, int N, class Expr>
  struct generator<nt2::tag::offset_diag_of_,Domain,N,Expr> : generate_as<Expr,0> {};

  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::offset_diag_of_,Domain,N,Expr> : boxed_size_of<Expr,3> {};
} } }

#endif
