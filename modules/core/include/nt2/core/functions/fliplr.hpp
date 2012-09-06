//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPLR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPLR_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::fliplr function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/relative.hpp>
#include <nt2/core/settings/shape.hpp>

namespace nt2
{
  namespace tag
  {
    struct fliplr_ : ext::elementwise_<fliplr_>
    {
      typedef ext::elementwise_<fliplr_> parent;
      typedef rectangular_           shape_type;
    };
  }

  //============================================================================
  /*!
   * upside down of a table. Return a table the columns of
   * which are in reverse order of the input
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::fliplr_       , fliplr, 1)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct  generator<nt2::tag::fliplr_,Domain,1,Expr>
        : relative_generator<Expr>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::fliplr_,Domain,1,Expr>
        : relative_size_of<Expr>
  {};

} } }

#endif
