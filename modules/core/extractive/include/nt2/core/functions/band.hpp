//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the band function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the band functor
    **/
    struct band_ : ext::elementwise_<band_>
    {
      typedef ext::elementwise_<band_> parent;
    };

    /*!
      @brief Tag for the offset_band1 functor
    **/
    struct offset_band1_ : ext::elementwise_<offset_band1_>
    {
      typedef ext::elementwise_<offset_band1_>  parent;
    };

    /*!
      @brief Tag for the offset_band2 functor
    **/
    struct offset_band2_ : ext::elementwise_<offset_band2_>
    {
      typedef ext::elementwise_<offset_band2_>  parent;
    };
  }

  /*!
    @brief Apply a diagonal masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    diagonal of the expression.

    @param a0 Expression to mask

    @par Alias:
    diagonal
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_         , band    , 1 )

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_         , diagonal, 1 )

  /*!
    @brief Apply a band masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    diagonal of the expression and a given number of super-diagonals.

    @param a0 Expression to mask
    @param a1 Number of super-diagional to include in the mask
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_band1_ , band    , 2 )

  /*!
    @brief Apply a dual band masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    diagonal of the expression, a given number of sub-diagonals and a given
    number of super-diagonals.

    @param a0 Expression to mask
    @param a1 Number of super-diagional to include in the mask
    @param a2 Number of sub-diagional to include in the mask
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_band2_ , band    , 3 )
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  value_type<nt2::tag::band_,Domain,1,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  value_type<nt2::tag::offset_band1_,Domain,2,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  value_type<nt2::tag::offset_band2_,Domain,3,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::band_,Domain,1,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::offset_band1_,Domain,2,Expr>
        : meta::size_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<nt2::tag::offset_band2_,Domain,3,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
