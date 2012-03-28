//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::band function
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/extractive_hierarchy.hpp>
#include <nt2/core/container/dsl/details/extractive.hpp>

namespace nt2
{
  namespace tag
  {
    struct band_ : ext::extractive_<band_>
    {
      typedef ext::extractive_<band_> parent;
      typedef diagonal_       shape_type;
    };

    struct offset_band1_ : ext::extractive_<offset_band1_>
    {
      typedef ext::extractive_<offset_band1_>  parent;
      typedef rectangular_                    shape_type;
    };

    struct offset_band2_ : ext::extractive_<offset_band2_>
    {
      typedef ext::extractive_<offset_band2_>  parent;
      typedef rectangular_                    shape_type;
    };
  }

  //============================================================================
  /*!
   * superior triangular part of a 2D table.
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_,         band, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_,     diagonal, 1) 
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_band1_, band, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_band2_, band, 3)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr, int N>
  struct  generator<nt2::tag::band_,Domain,N,Expr>
        : extractive_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  generator<nt2::tag::offset_band1_,Domain,N,Expr>
        : extractive_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  generator<nt2::tag::offset_band2_,Domain,N,Expr>
        : extractive_generator<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::band_,Domain,N,Expr>
        : extractive_size_of<Expr>
  {};

  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::offset_band1_,Domain,N,Expr>
        : extractive_size_of<Expr>
  {};
  
  template<class Domain, class Expr, int N>
  struct  size_of<nt2::tag::offset_band2_,Domain,N,Expr>
        : extractive_size_of<Expr>
  {};
} } }

#endif
