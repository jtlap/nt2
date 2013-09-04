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
  @brief Definition of fast_sincos function
**/

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_FAST_SINCOS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Hierarchy tag for fast_sincos function
    struct fast_sincos_ : ext::elementwise_<fast_sincos_>
    {
      typedef ext::elementwise_<fast_sincos_> parent;
    };
  }

  /*!
    @brief fast_sincos

    @c fast_sincos compute simultaneously the sin and cos of the input
    in the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @param a0 angle in radian

    @return A Fusion Sequence containing the sin and cos of @c a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sincos_, fast_sincos, 1)

  /*!
    @brief fast_sincos

    @c fast_sincos compute simultaneously the sin and cos of the input in
    the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @param a0 angle in radian
    @param a1 L-Value that will receive the sin off @c a0

    @return A Fusion Sequence containing the cos of @c a0
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&),2)

  /*!
    @brief  fast_sincos

    @c fast_sincos compute simultaneously the sin and cos of the input in
    the interval \f$[-\pi/4, \pi/4]\f$, nan outside.

    @param a0 angle in radian
    @param a1 L-Value that will receive the sin off @c a0
    @param a2 L-Value that will receive the cos off @c a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::fast_sincos_, fast_sincos,(A0 const&)(A1&)(A2&),3)
}

#endif
