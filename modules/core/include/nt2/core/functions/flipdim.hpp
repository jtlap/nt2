//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPDIM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPDIM_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::flipdim function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/details/relative.hpp>

namespace nt2
{
  namespace tag
  {
    struct flipdim_ : ext::elementwise_<flipdim_>
    {
      typedef ext::elementwise_<flipdim_> parent;
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
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::flipdim_       , flipdim, 2)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  generator<nt2::tag::flipdim_,Domain,N,Expr>
        : relative_generator<Expr>
  {};

  template<class Domain, class Expr>
  struct  size_of<nt2::tag::flipdim_,Domain,3,Expr>
        : relative_size_of<Expr>
  {};

} } }

#endif
