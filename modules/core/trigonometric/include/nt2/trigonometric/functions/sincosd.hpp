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
  @brief Definition of sincosd function
**/

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINCOSD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sincosd function
    struct sincosd_ : ext::elementwise_<sincosd_> { typedef ext::elementwise_<sincosd_> parent; };
  }
  /*!
    @brief sincosd

    @c sincosd compute simultaneously the sind and cosd of the input

    @param a0 angle in radian

    @return A Fusion Sequence containing the sind and cosd of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION(tag::sincosd_, sincosd, 1)

  /*!
    @brief sincosd

    @c sincosd compute simultaneously the sind and cosd of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the sind off @c a0

    @return A Fusion Sequence containing the cosd of @c a0
  **/


   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&),2)

  /*!
    @brief  sincosd

    @c sincosd compute simultaneously the sind and cosd of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the sind off @c a0
    @param a1 L-Value that will receive the cosd off @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincosd_, sincosd,(A0 const&)(A1&)(A2&),3)

    }

#endif
