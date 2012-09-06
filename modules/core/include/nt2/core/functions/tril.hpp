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
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/relative.hpp>
#include <nt2/core/settings/shape.hpp>

namespace nt2
{
  namespace tag
  {
    struct tril_ : ext::elementwise_<tril_>
    {
      typedef ext::elementwise_<tril_> parent;
      typedef lower_triangular_       shape_type;
    };

    struct offset_tril_ : ext::elementwise_<offset_tril_>
    {
      typedef ext::elementwise_<offset_tril_>  parent;
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
  template<class Domain, class Expr>
  struct  generator<nt2::tag::tril_,Domain,1,Expr>
        : relative_generator<Expr>
  {};

  template<class Domain, class Expr>
  struct  generator<nt2::tag::offset_tril_,Domain,2,Expr>
        : relative_generator<Expr>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::tril_,Domain,1,Expr>
        : relative_size_of<Expr>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::offset_tril_,Domain,2,Expr>
        : relative_size_of<Expr>
  {};
} } }

#endif
