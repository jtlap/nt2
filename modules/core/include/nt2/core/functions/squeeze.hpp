//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SQUEEZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SQUEEZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::squeeze function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>
#include <nt2/core/container/dsl/details/reshaping.hpp>

namespace nt2
{
  namespace tag
  {
    struct squeeze_ : ext::reshaping_<squeeze_>
    {
      typedef ext::reshaping_<squeeze_> parent;
    };
  }

  //============================================================================
  /*!
   * squeeze an expression by removing its singleton dimensions
   *
   * \param xpr   Expression to squeeze
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::squeeze_, squeeze, 1)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  generator<nt2::tag::squeeze_,Domain,2,Expr>
        : reshaping_generator<Expr>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::squeeze_,Domain,2,Expr>
        : reshaping_size_of<Expr>
  {};
} } }
#endif
