//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::tril function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/extractive_hierarchy.hpp>
#include <nt2/core/container/dsl/details/extractive.hpp>

namespace nt2
{
  namespace tag
  {
    struct tril_ : ext::extractive_<tril_>
    {
      typedef ext::extractive_<tril_> parent;
      typedef lower_triangular_       shape_type;
    };

    struct offset_tril_ : ext::extractive_<offset_tril_>
    {
      typedef ext::extractive_<offset_tril_>  parent;
      typedef rectangular_                    shape_type;
    };
  }

  //============================================================================
  /*!
   * inferior triangular part of a 2D table.
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tril_       , tril, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_tril_, tril, 2)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  generator<nt2::tag::tril_,Domain,N,Expr>
        : extractive_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  generator<nt2::tag::offset_tril_,Domain,N,Expr>
        : extractive_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::tril_,Domain,N,Expr>
        : extractive_size_of<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::offset_tril_,Domain,N,Expr>
        : extractive_size_of<Expr>
  {};
} } }

#endif
