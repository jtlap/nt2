//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
  @file
  @brief Definition of sincospi function
**/

#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sincospi function
    struct sincospi_ : ext::elementwise_<sincospi_> { typedef ext::elementwise_<sincospi_> parent; };
  }
  /*!
    @brief sincospi

    @c sincospi compute simultaneously the sinpi and cospi of the input

    @param a0 angle in radian

    @return A Fusion Sequence containing the sinpi and cospi of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sincospi_, sincospi, 1)

  /*!
    @brief sincospi

    @c sincospi compute simultaneously the sinpi and cospi of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the sinpi off @c a0

    @return A Fusion Sequence containing the cospi of @c a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1&),2)

  /*!
    @brief  sincospi

    @c sincospi compute simultaneously the sin and cospi of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the sinpi off @c a0
    @param a1 L-Value that will receive the cospi off @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1&)(A2&),3)

    }

#endif

